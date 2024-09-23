#include "tablelogagvshow.h"

TableLogAgvShow::TableLogAgvShow(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Дата технического обслуживания" << "S/N AGV" << "Наименование технического обслуживания" << "Табельный номер");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 250);
    tableWidget->setColumnWidth(1, 250);
    tableWidget->setColumnWidth(2, 350);
    tableWidget->setColumnWidth(3, 250);

    loadData();

    layout->addWidget(tableWidget);
    setLayout(layout);
}

void TableLogAgvShow::loadData() {
    tableWidget->setRowCount(3); // Пример: 3 строки

    tableWidget->setItem(0, 0, new QTableWidgetItem("23-09-24"));
    tableWidget->setItem(0, 1, new QTableWidgetItem("421011"));
    tableWidget->setItem(0, 2, new QTableWidgetItem("Корпус - очистка от загрязнений"));
    tableWidget->setItem(0, 3, new QTableWidgetItem("556949"));

    tableWidget->setItem(1, 0, new QTableWidgetItem("20-09-24"));
    tableWidget->setItem(1, 1, new QTableWidgetItem("321017"));
    tableWidget->setItem(1, 2, new QTableWidgetItem("Электрика - проверка работы звука"));
    tableWidget->setItem(1, 3, new QTableWidgetItem("200145"));

    tableWidget->setItem(2, 0, new QTableWidgetItem("18-09-24"));
    tableWidget->setItem(2, 1, new QTableWidgetItem("421022"));
    tableWidget->setItem(2, 2, new QTableWidgetItem("Подъемник - Проверить устан. штифты на кулачке"));
    tableWidget->setItem(2, 3, new QTableWidgetItem("776548"));
}
