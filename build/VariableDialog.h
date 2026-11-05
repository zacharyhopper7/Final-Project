#ifndef VARIABLEDIALOG_H
#define VARIABLEDIALOG_H

#include <QDialog>

class QLineEdit;

class VariableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit VariableDialog(QWidget *parent = nullptr);

    QString key() const;
    QString value() const;

    void setKey(const QString& key);
    void setValue(const QString& value);

private:
    QLineEdit *keyEdit;
    QLineEdit *valueEdit;
};

#endif