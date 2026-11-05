#include "VariableDialog.h"

#include <QDialogButtonBox>
#include <QFormLayout>
#include <QLineEdit>
#include <QMessageBox>
#include <QVBoxLayout>

VariableDialog::VariableDialog(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Environment Variable");

    keyEdit = new QLineEdit;
    valueEdit = new QLineEdit;

    QFormLayout *formLayout =
        new QFormLayout;

    formLayout->addRow("Variable:", keyEdit);
    formLayout->addRow("Value:", valueEdit);

    QDialogButtonBox *buttons =
        new QDialogButtonBox(
            QDialogButtonBox::Ok |
            QDialogButtonBox::Cancel);

    connect(buttons,
            &QDialogButtonBox::accepted,
            this,
            [this]()
    {
        if (keyEdit->text()
                .trimmed()
                .isEmpty())
        {
            QMessageBox::warning(
                this,
                "Validation Error",
                "Variable name cannot be empty.");
            return;
        }

        accept();
    });

    connect(buttons,
            &QDialogButtonBox::rejected,
            this,
            &QDialog::reject);

    QVBoxLayout *layout =
        new QVBoxLayout;

    layout->addLayout(formLayout);
    layout->addWidget(buttons);

    setLayout(layout);
}

QString VariableDialog::key() const
{
    return keyEdit->text();
}

QString VariableDialog::value() const
{
    return valueEdit->text();
}

void VariableDialog::setKey(const QString& key)
{
    keyEdit->setText(key);
}

void VariableDialog::setValue(const QString& value)
{
    valueEdit->setText(value);
}