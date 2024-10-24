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

    QPushButton *saveButton = new QPushButton("Сохранить изменения", this);
    saveButton->setStyleSheet(" background-color: #4CAF50; color: white;");
    connect(saveButton, &QPushButton::clicked, this, &UserEditDialog::saveData);

    deleteButton = new QPushButton("Удалить пользователя", this);
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

void UserEditDialog::deleteUser() {

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  QString("Вы точно хотите удалить пользователя с табельным номером с %1?").arg(user.getLogin()),
                                  QMessageBox::Yes | QMessageBox::No);

    // Проверяем, выбрал ли пользователь "Да"
    if (reply == QMessageBox::Yes) {
        // Здесь вы можете добавить код для удаления AGV из БД
        if (db->deleteUser(user.getLogin(),user.getName(),user.getSurname())) {
            qDebug() << "User deleted successfully.";
            accept(); // Закрываем диалог
        } else {
            qDebug() << "Failed to delete AGV.";
        }
    } else {
        qDebug() << "AGV deletion canceled.";
    }
}
