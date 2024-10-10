#ifndef MODELADDDIALOG_H
#define MODELADDDIALOG_H

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

class ModelAddDialog : public QDialog
{
    Q_OBJECT
public:
    ModelAddDialog(QWidget *parent = nullptr);

private slots:
    void addModel();

private:
    QPushButton *saveButton;
    QLineEdit *modelEdit;
    DataBase *db;
};

#endif // MODELADDDIALOG_H
