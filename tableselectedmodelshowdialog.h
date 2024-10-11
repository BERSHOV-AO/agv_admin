#ifndef TABLESELECTEDMODELSHOWDIALOG_H
#define TABLESELECTEDMODELSHOWDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QDateTime>
#include <QMessageBox>
#include "database.h"
#include <QBrush>
#include <QVBoxLayout>


class TableSelectedModelShowDialog : public QDialog
{
    Q_OBJECT
public:
    TableSelectedModelShowDialog(const QString &nameTableModel, QWidget *parent = nullptr);



private:
    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    DataBase *db;

    QPushButton *deleteButton;
    QPushButton *editButton;
    QString nameTableModel;

    void loadData();
//    QString formatDateFromMilliseconds(const QString& millisecondsStr);
//    QString addDaysToMilliseconds(const QString& millisecondsStr, const QString& daysStr);

private slots:
//    void oneEditAGVClicked();
//    void oneDeleteAGVClicked();
};

#endif // TABLESELECTEDMODELSHOWDIALOG_H
