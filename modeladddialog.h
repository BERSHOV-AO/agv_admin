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
#include <QCheckBox>
#include <QMap>
#include "database.h"
#include <modelagvitem.h>
#include "define_type_to.h"

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
    QCheckBox *defaultCheckBox;
    QMap <QString, QString> mapDafaultTO;
};

#endif // MODELADDDIALOG_H
