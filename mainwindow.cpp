#include "mainwindow.hpp"

#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QRegularExpression>
#include <QComboBox>
#include <qcombobox.h>
#include <qdebug.h>
#include <qlogging.h>
#include <qobject.h>
#include <QRadioButton>
#include <qradiobutton.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), process(new QProcess(this))
{

    auto *central = new QWidget;
    auto *layout = new QVBoxLayout;

    urlInput = new QLineEdit;
    urlInput->setPlaceholderText("Paste URL...");

    downloadButton = new QPushButton("Download");

    progressBar = new QProgressBar;
    progressBar->setRange(0, 100);

    resolutionComboBox = new QComboBox();
    resolutionComboBox->addItem("144p", 144);
    resolutionComboBox->addItem("240p", 240);
    resolutionComboBox->addItem("360p", 360);
    resolutionComboBox->addItem("480p", 480);
    resolutionComboBox->addItem("720p60", 720);
    resolutionComboBox->addItem("1080p60", 1080);
    resolutionComboBox->addItem("1440p60", 1440);
    resolutionComboBox->addItem("2160p60", 2160);

    mp4Button = new QRadioButton("mp4", this);
    mp3Button = new QRadioButton("mp3", this);
    mp4Button->setChecked(true);
    

    logOutput = new QTextEdit;
    logOutput->setReadOnly(true);

    layout->addWidget(urlInput);
    layout->addWidget(mp4Button);
    layout->addWidget(mp3Button);
    layout->addWidget(resolutionComboBox);
    layout->addWidget(downloadButton);
    layout->addWidget(progressBar);
    layout->addWidget(logOutput);

    central->setLayout(layout);
    setCentralWidget(central);

    connect(downloadButton, &QPushButton::clicked,
            this, &MainWindow::startDownload);

    connect(process, &QProcess::readyReadStandardOutput,
            this, &MainWindow::readOutput);

    connect(process, &QProcess::finished,
            this, &MainWindow::processFinished);

    connect(resolutionComboBox, &QComboBox::currentTextChanged,
            this, &MainWindow::setResolution);

    connect(mp4Button, &QRadioButton::toggled, 
            this, &MainWindow::setMP4);

    connect(mp3Button, &QRadioButton::toggled,
            this, &MainWindow::setMP3);
}

void MainWindow::startDownload()
{
    QString url = urlInput->text().trimmed();
    if (url.isEmpty())
        return;

    progressBar->setValue(0);
    logOutput->clear();

    QString program = "yt-dlp"; // assume it's in PATH
    QStringList args;
    if(mp3Button->isChecked()){
        args << "-x" 
             << "--audio-format" << "mp3" 
             << url;
    }
    else{
        args << "-S" << resolution 
             << "--merge-output-format" << "mp4"
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

void MainWindow::setResolution(const QString &){
    int height = resolutionComboBox->currentData().toInt();
    resolution = QString("height:%1").arg(height); 
    qDebug() << resolution;
}

void MainWindow::setMP4(bool selected){
    if(selected) qDebug() << "mp4 checked";
};

void MainWindow::setMP3(bool selected){
    if(selected) qDebug() << "mp3 checked";
    if(mp3Button->isChecked()){
       resolutionComboBox->setEnabled(false);
    }
    else resolutionComboBox->setEnabled(true);
};