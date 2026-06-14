#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QProcess>
#include <qcombobox.h>
#include <qobject.h>
#include <qradiobutton.h>

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
    void startDownload();
    void readOutput();
    void processFinished(int exitCode, QProcess::ExitStatus status);
    void setResolution(const QString &);
    void setMP4(bool selected);
    void setMP3(bool selected);
    
    private:
    QProcess *process;
    QLineEdit *urlInput;
    QPushButton *downloadButton;
    QProgressBar *progressBar;
    QTextEdit *logOutput;
    QComboBox *resolutionComboBox;
    QRadioButton *mp4Button;
    QRadioButton *mp3Button;
    QString resolution;
    QString fileType;
    
};

#endif