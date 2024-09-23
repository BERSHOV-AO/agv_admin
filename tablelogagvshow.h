#ifndef TABLELOGAGVSHOW_H
#define TABLELOGAGVSHOW_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

class TableLogAgvShow : public QWidget
{
    Q_OBJECT
public:
    explicit TableLogAgvShow(QWidget *parent = nullptr);
    QVBoxLayout *layout;
    QTableWidget *tableWidget;

    void loadData();

signals:

};

#endif // TABLELOGAGVSHOW_H
