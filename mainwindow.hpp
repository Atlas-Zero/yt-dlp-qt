#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QProcess>
#include <qcombobox.h>
#include <qobject.h>

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
    
    private:
    QProcess *process;
    QLineEdit *urlInput;
    QPushButton *downloadButton;
    QProgressBar *progressBar;
    QTextEdit *logOutput;
    QComboBox *resolutionComboBox;
    QString resolution;
    
};

#endif