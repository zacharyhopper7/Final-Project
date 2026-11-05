#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

class QTableWidget;
class QLineEdit;
class QPushButton;
class QPlainTextEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);

private slots:
    void browseExecutable();

    void addVariable();
    void editVariable();
    void removeVariable();

    void launchProcess();

    void readStdout();
    void readStderr();

    void processFinished(
        int exitCode,
        QProcess::ExitStatus exitStatus);

    void processError(
        QProcess::ProcessError error);

    void updateSelectionState();

private:
    void setupUi();

    QTableWidget *envTable;

    QLineEdit *executablePath;

    QPushButton *browseButton;
    QPushButton *launchButton;

    QPushButton *addButton;
    QPushButton *editButton;
    QPushButton *removeButton;

    QPlainTextEdit *outputArea;

    QProcess *process;
};

#endif