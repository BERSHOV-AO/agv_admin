#include "modeladddialog.h"

ModelAddDialog::ModelAddDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Добавление модели");

    db = new DataBase();
    db->connectToDataBase();

    modelEdit = new QLineEdit();
    modelEdit->setStyleSheet("background-color: white;");

    saveButton = new QPushButton("Добавить модель", this);
    saveButton->setStyleSheet(" background-color: #4CAF50; color: white;");
    connect(saveButton, &QPushButton::clicked, this, &ModelAddDialog::addModel);

    // Создаем вертикальный layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создаем лейблы и добавляем их в layout вместе с соответствующими QLineEdit

    layout->addWidget(new QLabel("Модель:", this));
    layout->addWidget(modelEdit);
    layout->addWidget(saveButton);

    // Устанавливаем основной layout для диалога
    setLayout(layout);
    setStyleSheet("background-color: #B0E0E6;");

    resize(300, 150);
}

void ModelAddDialog::addModel() {

    QString model = modelEdit->text();

    if(model.isEmpty()) {

        qDebug() << "Не все поля заполнены!";
        QMessageBox::warning(this, "Предупреждение", "Заполните название модели!");

    } else {
        db->saveModelItem(model);
        db->createNewModelTable(model);
        qDebug() << "Сохранена модель:";
        accept();
    }
}
