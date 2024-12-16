#include "settingdialog.h"

SettingDialog::SettingDialog(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Настройки TCP/IP");
    resize(300, 150);
    setStyleSheet("background-color: #B0E0E6;");

    // Создание вертикального лэйаута
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Создание горизонтального лэйаута для полей ввода
    QHBoxLayout *inputLayout = new QHBoxLayout();

    // Создание полей для ввода IP адреса
    for (int i = 0; i < 4; ++i) {
        QLineEdit *ipPart = new QLineEdit(this);
        ipPart->setFixedWidth(50); // Установка фиксированной ширины для полей ввода
        ipPart->setStyleSheet("background-color: white;");
        ipParts.append(ipPart);
        inputLayout->addWidget(ipPart);
        if (i < 3) {
            QLabel *dotLabel = new QLabel(".", this); // Добавление точки между частями
            inputLayout->addWidget(dotLabel);
        }
    }

    mainLayout->addLayout(inputLayout);

    // Создание вертикального лэйаута для кнопок
    QVBoxLayout *buttonLayout = new QVBoxLayout();

    // Кнопка для сохранения IP адреса
    saveButton = new QPushButton("Сохранить IP", this);
    saveButton->setStyleSheet("background-color: #4CAF50; color: white;");
    buttonLayout->addWidget(saveButton);

    // Кнопка отмены
    QPushButton *cancelButton = new QPushButton("Отмена", this);
    cancelButton->setStyleSheet("background-color: #f44336; color: white;"); // Красный фон для кнопки отмены
    buttonLayout->addWidget(cancelButton);

    // Установка минимального отступа между кнопками
    buttonLayout->setSpacing(5); // Установите нужное значение отступа

    mainLayout->addLayout(buttonLayout); // Добавляем вертикальный лэйаут с кнопками в основной лэйаут

    connect(saveButton, &QPushButton::clicked, this, &SettingDialog::saveIpToFile);
    connect(cancelButton, &QPushButton::clicked, this, &SettingDialog::reject); // Закрытие диалога при нажатии на кнопку "Отмена"
}

void SettingDialog::saveIpToFile() {
    // Проверка, что все поля заполнены
    for (QLineEdit *ipPart : ipParts) {
        if (ipPart->text().isEmpty()) {
            QMessageBox::warning(this, "Ошибка", "Пожалуйста, заполните все части IP адреса.");
            return;
        }
    }

    // Запись в файл
    QFile file("ip_config.txt");
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, "Ошибка", "Не удалось открыть файл для записи.");
        return;
    }

    QTextStream out(&file);
    out << ipParts[0]->text() << "."
        << ipParts[1]->text() << "."
        << ipParts[2]->text() << "."
        << ipParts[3]->text() << "\n";

    file.close();

    QMessageBox::information(this, "Успех", "IP адрес успешно сохранен.");
    accept();
}
