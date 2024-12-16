#ifndef SETTINGDIALOG_H
#define SETTINGDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>

class SettingDialog : public QDialog
{
    Q_OBJECT
public:
    SettingDialog(QWidget *parent = nullptr);
    QPushButton *saveButton;
    QList<QLineEdit*> ipParts;

private slots:
    void saveIpToFile();
};

#endif // SETTINGDIALOG_H
