#include "useradddialog.h"

UserAddDialog::UserAddDialog(QWidget *parent) : QDialog(parent)
{

    setWindowTitle("Добавлениe пользователя");

    db = new DataBase();
    db->connectToDataBase();

    nameEdit = new QLineEdit();
    nameEdit->setStyleSheet("background-color: white;");

    surnameEdit = new QLineEdit();
    surnameEdit->setStyleSheet("background-color: white;");

    loginEdit = new QLineEdit();
    loginEdit->setStyleSheet("background-color: white;");

    passEdit = new QLineEdit();
    passEdit->setStyleSheet("background-color: white;");
    //  passEdit->setEchoMode(QLineEdit::Password); // Скрываем ввод пароля

    // Кнопка для добавления пользователя
    saveButton = new QPushButton("Добавить пользователя", this);
    saveButton->setStyleSheet(" background-color: #4CAF50; color: white;");
    connect(saveButton, &QPushButton::clicked, this, &UserAddDialog::addUser);

    // Создаем вертикальный layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создаем лейблы и добавляем их в layout вместе с соответствующими QLineEdit
    layout->addWidget(new QLabel("Имя:", this));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("Фамилия:", this));
    layout->addWidget(surnameEdit);
    layout->addWidget(new QLabel("Логин/Табельный номер:", this));
    layout->addWidget(loginEdit);
    layout->addWidget(new QLabel("Пароль:", this));
    layout->addWidget(passEdit);
    layout->addWidget(saveButton);

    // Устанавливаем основной layout для диалога
    setLayout(layout);
    setStyleSheet("background-color: #B0E0E6;");

    resize(400, 280);
}

void UserAddDialog::addUser() {

    QString name = nameEdit->text();
    QString surname = surnameEdit->text();
    QString login = loginEdit->text();
    QString pass = passEdit->text();

    if(name.isEmpty() || surname.isEmpty() || login.isEmpty() || pass.isEmpty()) {

        qDebug() << "Не все поля заполнены!";
        QMessageBox::warning(this, "Предупреждение", "Не все поля заполнены!");

    } else {
        db->saveUserItem(name, surname, login, pass);
        qDebug() << "Сохранено User";
        nameEdit->clear();
        surnameEdit->clear();
        loginEdit->clear();
        passEdit->clear();
        accept();
    }
}
