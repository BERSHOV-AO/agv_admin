#ifndef TABLEAGVSHOW_H
#define TABLEAGVSHOW_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDateTime>
#include "database.h"

class TableAgvShow : public QWidget
{
    Q_OBJECT
public:
    explicit TableAgvShow(QWidget *parent = nullptr);
    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    DataBase *db;

    void loadData();
    QString formatDateFromMilliseconds(const QString& millisecondsStr);

signals:

};

#endif // TABLEAGVSHOW_H
