#ifndef AGVEDITDIALOG_H
#define AGVEDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QString>
#include <QComboBox>
#include <QDateTime>
#include <QDir>
#include <QMessageBox>
#include "database.h"
#include "agvitem.h"

class AGVEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AGVEditDialog(const AgvItem &agv, QWidget *parent = nullptr);
    AgvItem getAGV();

private slots:
    void saveData();

signals:
    void AGVDeleted();

private:
    AgvItem agv;
    QPushButton *saveButton;
    QLineEdit *nameEdit;
    QLineEdit *serilaNumberEdit;
    QLineEdit *fwVersionEdit;
    QLineEdit *modelEdit;
    QLineEdit *projectDocumentationEdit;
    DataBase *db;

    QComboBox *documentationComboBox;
    QComboBox *fwVersionComboBox;
    QComboBox *modelComboBox;

    qint64 getCurrentMillisecondsSinceEpoch();
};

#endif // AGVEDITDIALOG_H
