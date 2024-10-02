#ifndef TABLETOONEAGVSHOWDIALOG_H
#define TABLETOONEAGVSHOWDIALOG_H

#include <QDialog>
#include <QWidget>
#include <QVBoxLayout>
#include <QWidget>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QDateTime>
#include "database.h"
#include "agveditdialog.h"
#include "agvitem.h"


class TableToOneAgvShowDialog : public QDialog
{
    Q_OBJECT
public:
    TableToOneAgvShowDialog(const AgvItem &agv, QWidget *parent = nullptr);

private:
    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    DataBase *db;

    QPushButton *deleteButton;
    QPushButton *editButton;
    AgvItem agv;



private slots:
    void oneEditAGVClicked();
    void oneDeleteAGVClicked();
};

#endif // TABLETOONEAGVSHOWDIALOG_H
