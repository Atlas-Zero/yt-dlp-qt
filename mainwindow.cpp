#include "mainwindow.hpp"

#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QRegularExpression>
#include <QComboBox>
#include <QDebug>
#include <QObject>
#include <QRadioButton>
#include <qlogging.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), process(new QProcess(this))
{

    auto *central = new QWidget;
    auto *layout = new QVBoxLayout;

    urlInput = new QLineEdit;
    urlInput->setPlaceholderText("Paste URL...");

    resolutionComboBox = new QComboBox();
    resolutionComboBox->addItem("2160p60", 2160);
    resolutionComboBox->addItem("1440p60", 1440);
    resolutionComboBox->addItem("1080p60", 1080);
    resolutionComboBox->addItem("720p60", 720);
    resolutionComboBox->addItem("480p", 480);
    resolutionComboBox->addItem("360p", 360);
    resolutionComboBox->addItem("240p", 240);
    resolutionComboBox->addItem("144p", 144);

    auto *hbox = new QHBoxLayout;

    // audio
    audioGroup = new QGroupBox("Audio");
    audioLayout = new QVBoxLayout();

    QStringList audioFormats = {"mp3", "wav", "flac", "m4a", "aac", "opus"};
    for (const QString &format : audioFormats)
    {
        QPushButton *btn = new QPushButton(format.toUpper());
        btn->connect(btn, &QPushButton::clicked, this, [this, format]()
                     { 
                        fileType = format; 
                        startDownload(true); 
                        qDebug() << "download:" << format; });
        audioLayout->addWidget(btn);
    }

    audioGroup->setLayout(audioLayout);
    hbox->addWidget(audioGroup);

    // video
    videoGroup = new QGroupBox("Video");
    videoLayout = new QVBoxLayout();

    QStringList videoFormats = {"mp4", "mkv", "webm", "avi", "mov", "flv"};
    for (const QString &format : videoFormats)
    {
        QPushButton *btn = new QPushButton(format.toUpper());
        btn->connect(btn, &QPushButton::clicked, this, [this, format]()
                     { 
                        fileType = format; 
                        startDownload(false); 
                        qDebug() << "download:" << format; });
        videoLayout->addWidget(btn);
    }

    videoGroup->setLayout(videoLayout);
    hbox->addWidget(videoGroup);

    progressBar = new QProgressBar;
    progressBar->setRange(0, 100);

    logOutput = new QTextEdit;
    logOutput->setReadOnly(true);

    layout->addWidget(urlInput);
    layout->addWidget(resolutionComboBox);
    layout->addLayout(hbox);
    layout->addWidget(progressBar);
    layout->addWidget(logOutput);

    central->setLayout(layout);
    setCentralWidget(central);

    connect(process, &QProcess::readyReadStandardOutput,
            this, &MainWindow::readOutput);

    connect(process, &QProcess::finished,
            this, &MainWindow::processFinished);

    connect(resolutionComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::setResolution);
}

void MainWindow::startDownload(bool isAudio)
{
    QString url = urlInput->text().trimmed();
    if (url.isEmpty())
        return;

    progressBar->setValue(0);
    logOutput->clear();

    QString program = "yt-dlp"; // assume it's in PATH
    QStringList args;
    if (isAudio)
    {
        args << "-x"
             << "--audio-format" << fileType
             << url;
    }
    else
    {
        args << "-S" << resolution
             << "--merge-output-format" << fileType
             << url;
    }

    process->start(program, args);
}

void MainWindow::readOutput()
{
    QString output = process->readAllStandardOutput();
    logOutput->append(output);

    // 1-2 decimals + . + 1-2 decimals + %
    QRegularExpression re(R"((\d+(\.\d+)?)%)");
    auto match = re.match(output);

    if (match.hasMatch())
    {
        int percent = match.captured(1).toDouble();
        progressBar->setValue(percent);
    }
}

void MainWindow::processFinished(int exitCode, QProcess::ExitStatus status)
{
    logOutput->append("\nFinished.");
    progressBar->setValue(100);
}

void MainWindow::setResolution(const QString &)
{
    int height = resolutionComboBox->currentData().toInt();
    resolution = QString("height:%1").arg(height);
    qDebug() << resolution;
}
