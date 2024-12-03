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
#include <QMessageBox>
#include "database.h"
#include "agv_headers/agveditdialog.h"
#include "entities_headers/agvitem.h"
#include "entities_headers/agvtoitem.h"
#include <QBrush>

#define DELETE_AGV_STRING  "Удаление AGV из базы данных"

class TableToOneAgvShowDialog : public QDialog
{
    Q_OBJECT
public:
    TableToOneAgvShowDialog(const AgvItem &agv, QWidget *parent = nullptr);

private:
    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    DataBase& db = DataBase::getInstance();

    QPushButton *deleteButton;
    QPushButton *editButton;
    AgvItem agv;

    void loadData();
    QString formatDateFromMilliseconds(const QString& millisecondsStr);
    QString addDaysToMilliseconds(const QString& millisecondsStr, const QString& daysStr);
    qint64 getCurrentMillisecondsSinceEpoch();

private slots:
    void oneEditAGVClicked();
    void oneDeleteAGVClicked();
};

#endif // TABLETOONEAGVSHOWDIALOG_H
