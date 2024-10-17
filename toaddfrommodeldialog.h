#ifndef TOADDFROMMODELDIALOG_H
#define TOADDFROMMODELDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QDir>
#include <QDateTime>
#include "database.h"
#include <modelagvitem.h>

class ToAddFromModelDialog : public QDialog
{
public:
    ToAddFromModelDialog(const QString &nameTableModel, QWidget *parent = nullptr);

private:
    QString nameTableModel;
    QPushButton *saveButton;
    QLineEdit *nameTo;
    QLineEdit *frequencyTo;
    DataBase *db;

private slots:
    void addTo();


};

#endif // TOADDFROMMODELDIALOG_H
