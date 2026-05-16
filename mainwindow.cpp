#include "mainwindow.hpp"

#include <QLineEdit>
#include <QPushButton>
#include <QProgressBar>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QRegularExpression>

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

    logOutput = new QTextEdit;
    logOutput->setReadOnly(true);

    layout->addWidget(urlInput);
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
    args << url;

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
