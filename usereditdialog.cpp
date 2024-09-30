#include "usereditdialog.h"

UserEditDialog::UserEditDialog(const UserItem &user, QWidget *parent)
    : QDialog(parent), user(user) {
    setWindowTitle("Редактирование пользователя");

    nameEdit = new QLineEdit(user.getName(), this);
    surnameEdit = new QLineEdit(user.getSurname(), this);
    loginEdit = new QLineEdit(user.getLogin(), this);
    passEdit = new QLineEdit(user.getPass(), this);
   // passEdit->setEchoMode(QLineEdit::Password);

    QPushButton *saveButton = new QPushButton("Сохранить", this);
    connect(saveButton, &QPushButton::clicked, this, &UserEditDialog::saveData);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(nameEdit);
    layout->addWidget(surnameEdit);
    layout->addWidget(loginEdit);
    layout->addWidget(passEdit);
    layout->addWidget(saveButton);

    setLayout(layout);
}

UserItem UserEditDialog::getUser() const {
    return UserItem(nameEdit->text(), surnameEdit->text(), loginEdit->text(), passEdit->text());
}

void UserEditDialog::saveData() {

     qDebug() << "saveData user";
    // Здесь вы можете добавить код для сохранения данных в БД
    accept();
}
