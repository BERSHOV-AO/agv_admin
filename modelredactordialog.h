#ifndef MODELREDACTORDIALOG_H
#define MODELREDACTORDIALOG_H

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
#include <QTableWidget>
#include <QHeaderView>
#include "database.h"
#include "modelagvitem.h"
#include "modeladddialog.h"


class ModelRedactorDialog : public QDialog
{
public:
    ModelRedactorDialog(QWidget *parent = nullptr);

private:

    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    QPushButton *addModelButton;
    DataBase *db;

    void loadData();

private slots:
    void onAddModelClicked();

};

#endif // MODELREDACTORDIALOG_H
