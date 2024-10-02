#include "tabletooneagvshowdialog.h"

TableToOneAgvShowDialog::TableToOneAgvShowDialog(const AgvItem &agv, QWidget *parent) : QDialog(parent), agv(agv)
{


    db = new DataBase();
    db->connectToDataBase();

    deleteButton = new QPushButton("Удалить AGV", this);
    deleteButton->setStyleSheet("background-color: red; color: white;");
    connect(deleteButton, &QPushButton::clicked, this, &TableToOneAgvShowDialog::oneDeleteAGVClicked);

    editButton = new QPushButton("Редактировать AGV", this);
    editButton->setStyleSheet("background-color: #4986cf; color: white;");
    connect(editButton, &QPushButton::clicked, this, &TableToOneAgvShowDialog::oneEditAGVClicked);

    layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Деталь/Наименование работ" << "Дата последнего обслуживания" << "Дата следующего обслуживания");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 250);
    tableWidget->setColumnWidth(1, 250);
    tableWidget->setColumnWidth(2, 370);
    tableWidget->setColumnWidth(3, 250);

    // loadData();


    // Создаем горизонтальный layout для кнопок
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(editButton);

    layout->addWidget(tableWidget);

    // Добавляем кнопки в основной layout
    layout->addLayout(buttonLayout);

    setLayout(layout);
}


void TableToOneAgvShowDialog::oneEditAGVClicked() {
    AGVEditDialog editDialog(agv, this);

    if (editDialog.exec() == QDialog::Accepted) {
        //        AgvItem updatedUser = editDialog.getUser()
    }
}

void TableToOneAgvShowDialog::oneDeleteAGVClicked() {


    // Здесь вы можете добавить код для удаления пользователя из БД
    if (db->deleteAgv(agv.getSerialNumber())) { // Предполагается, что у вас есть метод deleteUser в классе db
        qDebug() << "User deleted successfully.";
        // emit userDeleted(); // Сигнал для уведомления о том, что пользователь был удален
        accept(); // Закрываем диалог
    } else {
        qDebug() << "Failed to delete user.";
    }
}
