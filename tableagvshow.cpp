#include "tableagvshow.h"

TableAgvShow::TableAgvShow(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "ID" << "Название" << "Статус");
    loadData();

    layout->addWidget(tableWidget);
    setLayout(layout);
}

void TableAgvShow::loadData() {
    tableWidget->setRowCount(3); // Пример: 3 строки

    tableWidget->setItem(0, 0, new QTableWidgetItem("1"));
    tableWidget->setItem(0, 1, new QTableWidgetItem("AGV-1"));
    tableWidget->setItem(0, 2, new QTableWidgetItem("Доступен"));

    tableWidget->setItem(1, 0, new QTableWidgetItem("2"));
    tableWidget->setItem(1, 1, new QTableWidgetItem("AGV-2"));
    tableWidget->setItem(1, 2, new QTableWidgetItem("Занят"));

    tableWidget->setItem(2, 0, new QTableWidgetItem("3"));
    tableWidget->setItem(2, 1, new QTableWidgetItem("AGV-3"));
    tableWidget->setItem(2, 2, new QTableWidgetItem("Недоступен"));
}
