#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QProcess>
#include <QComboBox>
#include <QGroupBox>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QObject>

class QLineEdit;
class QPushButton;
class QProgressBar;
class QTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private slots:
    void startDownload(bool isAudio);
    void readOutput();
    void processFinished(int exitCode, QProcess::ExitStatus status);
    void setResolution(const QString &);

private:
    QProcess *process;
    QLineEdit *urlInput;
    QComboBox *resolutionComboBox;
    QHBoxLayout *hBox;
    QGroupBox *audioGroup;
    QVBoxLayout *audioLayout;
    QGroupBox *videoGroup;
    QVBoxLayout *videoLayout;
    QProgressBar *progressBar;
    QTextEdit *logOutput;
    QGroupBox *formatGroupBox;
    QString resolution;
    QString fileType;
};

#endif