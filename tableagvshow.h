#ifndef TABLEAGVSHOW_H
#define TABLEAGVSHOW_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>

class TableAgvShow : public QWidget
{
    Q_OBJECT
public:
    explicit TableAgvShow(QWidget *parent = nullptr);
    QVBoxLayout *layout;
    QTableWidget *tableWidget;

    void loadData();

signals:

};

#endif // TABLEAGVSHOW_H
