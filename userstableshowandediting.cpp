#include "userstableshowandediting.h"

UsersTableShowAndEditing::UsersTableShowAndEditing(QWidget *parent) : QWidget(parent)
{

    db = new DataBase();
    db->connectToDataBase();

    layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Имя" << "Фамилия" << "Логин/Табельный Номер" << "Пароль");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 250);
    tableWidget->setColumnWidth(1, 250);
    tableWidget->setColumnWidth(2, 370);
    tableWidget->setColumnWidth(3, 250);

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, &UsersTableShowAndEditing::onCellDoubleClicked);

    loadData();

    layout->addWidget(tableWidget);
    setLayout(layout);
}

void UsersTableShowAndEditing::loadData() {

    QList<UserItem> users = db->fetchUsers(); // Получаем данные

    // Очищаем таблицу перед загрузкой новых данных
    tableWidget->setRowCount(0);

    // Заполняем таблицу данными из списка agvs
    for (const UserItem &user : users) {
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount); // Добавляем новую строку

        tableWidget->setItem(rowCount, 0, new QTableWidgetItem(user.getName()));
        tableWidget->setItem(rowCount, 1, new QTableWidgetItem(user.getSurname()));
        tableWidget->setItem(rowCount, 2, new QTableWidgetItem(user.getLogin()));
        tableWidget->setItem(rowCount, 3, new QTableWidgetItem(user.getPass()));
    }
}


void UsersTableShowAndEditing::onCellDoubleClicked(int row, int column) {
    if (row < 0) return; // Проверка на корректность строки

    // Получаем данные выбранного пользователя
    QString name = tableWidget->item(row, 0)->text();
    QString surname = tableWidget->item(row, 1)->text();
    QString login = tableWidget->item(row, 2)->text();
    QString pass = tableWidget->item(row, 3)->text();

    UserItem selectedUser(name, surname, login, pass);

    // Открываем диалог для редактирования
    UserEditDialog editDialog(selectedUser, this);
    if (editDialog.exec() == QDialog::Accepted) {
        UserItem updatedUser = editDialog.getUser();

        // Обновляем данные в таблице
        tableWidget->item(row, 0)->setText(updatedUser.getName());
        tableWidget->item(row, 1)->setText(updatedUser.getSurname());
        tableWidget->item(row, 2)->setText(updatedUser.getLogin());
        tableWidget->item(row, 3)->setText(updatedUser.getPass());

        if (db->updateUser(login, updatedUser.getName(), updatedUser.getSurname(), updatedUser.getPass())) {
            qDebug() << "User updated successfully.";
        } else {
            qDebug() << "Failed to update user.";
        }
    }
}



