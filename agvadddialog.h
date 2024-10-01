#ifndef AGVADDDIALOG_H
#define AGVADDDIALOG_H

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

#define ADD_AGV_STRING  "Добавление AGV в базу данных"

class AGVAddDialog : public QDialog
{
    Q_OBJECT
public:
    AGVAddDialog(QWidget *parent = nullptr);

private slots:
    void addAGV();

private:
    QPushButton *saveButton;
    QLineEdit *nameEdit;
    QLineEdit *serilaNumberEdit;
    QLineEdit *fwVersionEdit;
    QLineEdit *modelEdit;
    QLineEdit *projectDocumentationEdit;
    DataBase *db;

    QComboBox *documentationComboBox;
    QComboBox *fwVersionComboBox;

    qint64 getCurrentMillisecondsSinceEpoch();
};

#endif // AGVADDDIALOG_H

