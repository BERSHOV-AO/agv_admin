#include "main_window_tables_headers/userstableshowandediting.h"

UsersTableShowAndEditing::UsersTableShowAndEditing(QWidget *parent) : QWidget(parent)
{

    db.connectToDataBase();

    layout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout();

    addUserButton = new QPushButton("Добавить пользователя", this);
    addUserButton->setStyleSheet("background-color: #4986cf; color: white; font-size: 16px; font-family: Arial; font-weight: bold;");
    addUserButton->setFixedSize(250, 35);
    connect(addUserButton, &QPushButton::clicked, this, &UsersTableShowAndEditing::onAddUserClicked);

    // Spacer для отталкивания кнопки к правому краю
    topLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    topLayout->addWidget(addUserButton);
    // Добавляем горизонтальный макет в основной вертикальный макет
    layout->addLayout(topLayout);

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Имя" << "Фамилия" << "Логин/Табельный Номер" << "Пароль");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 270);
    tableWidget->setColumnWidth(1, 270);
    tableWidget->setColumnWidth(2, 370);
    tableWidget->setColumnWidth(3, 270);

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    // Устанавливаем растяжение последнего столбца
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Устанавливаем политику растягивания для всех столбцов
    for (int i = 0; i < tableWidget->columnCount(); ++i) {
        tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, &UsersTableShowAndEditing::onCellDoubleClicked);

    loadData();

    layout->addWidget(tableWidget);
    setLayout(layout);
}

void UsersTableShowAndEditing::loadData() {

    QList<UserItem> users = db.fetchUsers();

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

void UsersTableShowAndEditing::onAddUserClicked() {

    UserAddDialog addDialog(this);
    if (addDialog.exec() == QDialog::Accepted) {
        qDebug() << "update table";
        loadData();
    }
}

void UsersTableShowAndEditing::onCellDoubleClicked(int row) {
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
        loadData();
    }
}

void UsersTableShowAndEditing::updateTable() {
    // Очистите таблицу
    //  tableWidget->clearContents();

    // Загрузите новые данные из базы данных и заполните таблицу
    // loadData(); // Предполагается, что у вас есть метод loadData для загрузки данных
}




