#include "userstableshowandediting.h"

UsersTableShowAndEditing::UsersTableShowAndEditing(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Логин/Табельный Номер" << "Email" << "Пароль");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 250);
    tableWidget->setColumnWidth(1, 250);
    tableWidget->setColumnWidth(2, 370);

    loadData();

    layout->addWidget(tableWidget);
    setLayout(layout);

}

void UsersTableShowAndEditing::loadData() {
    tableWidget->setRowCount(3); // Пример: 3 строки

    tableWidget->setItem(0, 0, new QTableWidgetItem("556949"));
    tableWidget->setItem(0, 1, new QTableWidgetItem("wds@mail.ru"));
    tableWidget->setItem(0, 2, new QTableWidgetItem("121286"));

    tableWidget->setItem(1, 0, new QTableWidgetItem("200145"));
    tableWidget->setItem(1, 1, new QTableWidgetItem("ffdfd@mail.ru"));
    tableWidget->setItem(1, 2, new QTableWidgetItem("12345"));


    tableWidget->setItem(2, 0, new QTableWidgetItem("776548"));
    tableWidget->setItem(2, 1, new QTableWidgetItem("sdsdsds@mail.ru"));
    tableWidget->setItem(2, 2, new QTableWidgetItem("77777"));
}
