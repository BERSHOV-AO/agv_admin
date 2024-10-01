#include "usereditdialog.h"

UserEditDialog::UserEditDialog(const UserItem &user, QWidget *parent)
    : QDialog(parent), user(user) {
    setWindowTitle("Управление настройками пользователя");

    db = new DataBase();
    db->connectToDataBase();

    nameEdit = new QLineEdit(user.getName(), this);
    nameEdit->setStyleSheet("background-color: white;");
    surnameEdit = new QLineEdit(user.getSurname(), this);
    surnameEdit->setStyleSheet("background-color: white;");
    loginEdit = new QLineEdit(user.getLogin(), this);
    loginEdit->setStyleSheet("background-color: white;");
    passEdit = new QLineEdit(user.getPass(), this);
    passEdit->setStyleSheet("background-color: white;");
    // passEdit->setEchoMode(QLineEdit::Password);

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    saveButton->setStyleSheet(" background-color: #4CAF50; color: white;");
    connect(saveButton, &QPushButton::clicked, this, &UserEditDialog::saveData);

    deleteButton = new QPushButton("Удалить", this);
    deleteButton->setStyleSheet("background-color: red; color: white;");
    connect(deleteButton, &QPushButton::clicked, this, &UserEditDialog::deleteUser);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Имя:", this));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("Фамилия:", this));
    layout->addWidget(surnameEdit);
    layout->addWidget(new QLabel("Логин:", this));
    layout->addWidget(loginEdit);
    layout->addWidget(new QLabel("Пароль:", this));
    layout->addWidget(passEdit);
    layout->addWidget(saveButton);
    layout->addWidget(deleteButton);

    setLayout(layout);
    setStyleSheet("background-color: #B0E0E6;");

    resize(400, 300);
}

UserItem UserEditDialog::getUser() const {
    return UserItem(nameEdit->text(), surnameEdit->text(), loginEdit->text(), passEdit->text());
}

void UserEditDialog::saveData() {

    qDebug() << "saveData user";
    // Здесь вы можете добавить код для сохранения данных в БД
    accept();
}

//void UserEditDialog::deleteUser() {

//    qDebug() << "saveData user";
//    // Здесь вы можете добавить код для сохранения данных в БД


//    accept();
//}

//bool DataBase::deleteUser(const QString &login, const QString &name, const QString &surname) {

void UserEditDialog::deleteUser() {
    // Здесь вы можете добавить код для удаления пользователя из БД
    if (db->deleteUser(user.getLogin(),user.getName(),user.getSurname())) { // Предполагается, что у вас есть метод deleteUser в классе db
        qDebug() << "User deleted successfully.";
        emit userDeleted(); // Сигнал для уведомления о том, что пользователь был удален
        accept(); // Закрываем диалог
    } else {
        qDebug() << "Failed to delete user.";
    }
}
