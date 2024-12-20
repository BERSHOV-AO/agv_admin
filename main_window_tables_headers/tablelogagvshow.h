#ifndef TABLELOGAGVSHOW_H
#define TABLELOGAGVSHOW_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDateTime>
#include <database.h>
#include "entities_headers/logitem.h"

class TableLogAgvShow : public QWidget
{
    Q_OBJECT
public:
    explicit TableLogAgvShow(QWidget *parent = nullptr);
    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    DataBase& db = DataBase::getInstance();

    void loadData();
    QString formatDateFromMilliseconds(const QString& millisecondsStr);

signals:

};

#endif // TABLELOGAGVSHOW_H
