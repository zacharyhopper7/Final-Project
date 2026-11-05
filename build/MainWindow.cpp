#include "MainWindow.h"
#include "VariableDialog.h"

#include <QFileDialog>
#include <QFileInfo>
#include <QGroupBox>
#include <QHeaderView>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QPlainTextEdit>
#include <QProcessEnvironment>
#include <QPushButton>
#include <QStatusBar>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>
#include <QWidget>
#include <QLineEdit>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    process = new QProcess(this);

    setupUi();

    connect(process,
            &QProcess::readyReadStandardOutput,
            this,
            &MainWindow::readStdout);

    connect(process,
            &QProcess::readyReadStandardError,
            this,
            &MainWindow::readStderr);

    connect(process,
            &QProcess::finished,
            this,
            &MainWindow::processFinished);

    connect(process,
            &QProcess::errorOccurred,
            this,
            &MainWindow::processError);
}

void MainWindow::setupUi()
{
    setWindowTitle("env-gui+");
    resize(900, 650);

    QWidget *centralWidget = new QWidget;
    setCentralWidget(centralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    envTable = new QTableWidget;
    envTable->setColumnCount(2);
    envTable->setHorizontalHeaderLabels(
        {"Variable", "Value"});

    envTable->horizontalHeader()
        ->setStretchLastSection(true);

    addButton = new QPushButton("Add");
    editButton = new QPushButton("Edit");
    removeButton = new QPushButton("Remove");

    editButton->setEnabled(false);
    removeButton->setEnabled(false);

    connect(envTable,
            &QTableWidget::itemSelectionChanged,
            this,
            &MainWindow::updateSelectionState);

    connect(addButton,
            &QPushButton::clicked,
            this,
            &MainWindow::addVariable);

    connect(editButton,
            &QPushButton::clicked,
            this,
            &MainWindow::editVariable);

    connect(removeButton,
            &QPushButton::clicked,
            this,
            &MainWindow::removeVariable);

    QHBoxLayout *envButtons = new QHBoxLayout;

    envButtons->addWidget(addButton);
    envButtons->addWidget(editButton);
    envButtons->addWidget(removeButton);

    QVBoxLayout *envLayout = new QVBoxLayout;
    envLayout->addWidget(envTable);
    envLayout->addLayout(envButtons);

    QGroupBox *envGroup =
        new QGroupBox("Environment Variables");

    envGroup->setLayout(envLayout);

    executablePath = new QLineEdit;
    executablePath->setReadOnly(true);

    browseButton = new QPushButton("Browse...");

    connect(browseButton,
            &QPushButton::clicked,
            this,
            &MainWindow::browseExecutable);

    QHBoxLayout *execLayout = new QHBoxLayout;

    execLayout->addWidget(executablePath);
    execLayout->addWidget(browseButton);

    QGroupBox *execGroup =
        new QGroupBox("Executable");

    execGroup->setLayout(execLayout);

    launchButton = new QPushButton("Launch");
    launchButton->setEnabled(false);

    connect(launchButton,
            &QPushButton::clicked,
            this,
            &MainWindow::launchProcess);

    outputArea = new QPlainTextEdit;
    outputArea->setReadOnly(true);

    QGroupBox *outputGroup =
        new QGroupBox("Process Output");

    QVBoxLayout *outputLayout =
        new QVBoxLayout;

    outputLayout->addWidget(outputArea);

    outputGroup->setLayout(outputLayout);

    mainLayout->addWidget(envGroup);
    mainLayout->addWidget(execGroup);
    mainLayout->addWidget(launchButton);
    mainLayout->addWidget(outputGroup);

    centralWidget->setLayout(mainLayout);

    statusBar()->showMessage("Ready");
}

void MainWindow::browseExecutable()
{
    QString file =
        QFileDialog::getOpenFileName(
            this,
            "Select Executable");

    if (!file.isEmpty())
    {
        executablePath->setText(file);
        launchButton->setEnabled(true);
    }
}

void MainWindow::addVariable()
{
    VariableDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted)
    {
        int row = envTable->rowCount();

        envTable->insertRow(row);

        envTable->setItem(
            row,
            0,
            new QTableWidgetItem(dialog.key()));

        envTable->setItem(
            row,
            1,
            new QTableWidgetItem(dialog.value()));
    }
}

void MainWindow::editVariable()
{
    int row = envTable->currentRow();

    if (row < 0)
        return;

    VariableDialog dialog(this);

    dialog.setKey(
        envTable->item(row, 0)->text());

    dialog.setValue(
        envTable->item(row, 1)->text());

    if (dialog.exec() == QDialog::Accepted)
    {
        envTable->item(row, 0)
            ->setText(dialog.key());

        envTable->item(row, 1)
            ->setText(dialog.value());
    }
}

void MainWindow::removeVariable()
{
    int row = envTable->currentRow();

    if (row >= 0)
    {
        envTable->removeRow(row);
    }
}

void MainWindow::launchProcess()
{
    QString executable =
        executablePath->text();

    QFileInfo info(executable);

    if (!info.exists())
    {
        QMessageBox::critical(
            this,
            "Error",
            "Executable not found.");
        return;
    }

    if (!info.isExecutable())
    {
        QMessageBox::critical(
            this,
            "Error",
            "Selected file is not executable.");
        return;
    }

    outputArea->clear();

    QProcessEnvironment env =
        QProcessEnvironment::
            systemEnvironment();

    for (int row = 0;
         row < envTable->rowCount();
         row++)
    {
        QString key =
            envTable->item(row, 0)->text();

        QString value =
            envTable->item(row, 1)->text();

        env.insert(key, value);
    }

    process->setProcessEnvironment(env);

    process->start(executable);

    statusBar()->showMessage(
        "Process started");

    launchButton->setEnabled(false);
}

void MainWindow::readStdout()
{
    outputArea->appendPlainText(
        QString::fromUtf8(
            process->readAllStandardOutput()));
}

void MainWindow::readStderr()
{
    outputArea->appendPlainText(
        "[stderr] " +
        QString::fromUtf8(
            process->readAllStandardError()));
}

void MainWindow::processFinished(
        int exitCode,
        QProcess::ExitStatus)
{
    QString message =
        QString(
            "\nProcess finished.\nExit Code: %1")
            .arg(exitCode);

    outputArea->appendPlainText(message);

    statusBar()->showMessage(message);

    launchButton->setEnabled(true);
}

void MainWindow::processError(
        QProcess::ProcessError)
{
    QMessageBox::critical(
        this,
        "Process Error",
        process->errorString());

    launchButton->setEnabled(true);
}

void MainWindow::updateSelectionState()
{
    bool selected =
        envTable->currentRow() >= 0;

    editButton->setEnabled(selected);
    removeButton->setEnabled(selected);
}