#include "addagvwidget.h"

AddAGVWidget::AddAGVWidget(QWidget *parent) : QWidget(parent)
{
    layout = new QVBoxLayout(this);

    // Устанавливаем отступы для верхней части
    layout->setContentsMargins(0, 10, 0, 300); // Уменьшаем верхний отступ

    // Центрируем заголовок
    QLabel *titleLabel = new QLabel("Добавить AGV");
    titleLabel->setAlignment(Qt::AlignCenter); // Центрируем текст в QLabel
    titleLabel->setStyleSheet("font-size: 20px; font-weight: bold;");


    QHBoxLayout *titleLayout = new QHBoxLayout();
    titleLayout->addStretch(); // добавляем отступ слева
    titleLayout->addWidget(titleLabel); // добавляем заголовок
    titleLayout->addStretch(); // добавляем отступ справа

    layout->addLayout(titleLayout); // добавляем горизонтальный layout с заголовком в основной

    formLayout = new QFormLayout;

    nameLineEdit = new QLineEdit(this);
    nameLineEdit->setFixedSize(300, 30);
    serialNumberLineEdit = new QLineEdit(this);
    serialNumberLineEdit->setFixedSize(300, 30);
    modelLineEdit = new QLineEdit(this);
    modelLineEdit->setFixedSize(300, 30);
    this->setStyleSheet("QLineEdit { background-color: white; font-size: 16px;}");


    //---------------------combo box FW---------------------------
    fwVersionComboBox = new QComboBox(this);
    fwVersionComboBox->setFixedSize(300, 30);
    // Получаем список директорий
    QDir dirFW("C:/wamp64/www/host/fw");
    QStringList directoriesFW = dirFW.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    fwVersionComboBox->addItems(directoriesFW);
    //----------------------------------------------------------

    //---------------------combo box sPlan---------------------------
    documentationComboBox = new QComboBox(this);
    documentationComboBox->setFixedSize(300, 30);
    // Получаем список директорий
    QDir dir("C:/wamp64/www/host/schemes");
    QStringList directories = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    documentationComboBox->addItems(directories);
    //----------------------------------------------------------

    formLayout->addRow("Название AGV:", nameLineEdit);
    formLayout->addRow("Серийный номер:", serialNumberLineEdit);
    formLayout->addRow("Версия FW:", fwVersionComboBox);
    formLayout->addRow("Модель AGV:", modelLineEdit);
    formLayout->addRow("Проектная документация:", documentationComboBox);

    // Создаем контейнер для формы
    QWidget *formContainer = new QWidget();
    formContainer->setLayout(formLayout);

    // Создаем горизонтальный layout для центрирования формы
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addStretch(); // добавляем отступ слева
    hLayout->addWidget(formContainer); // добавляем форму
    hLayout->addStretch(); // добавляем отступ справа

    layout->addLayout(hLayout); // добавляем горизонтальный layout в основной

    // Кнопка для сохранения AGV
    saveButton = new QPushButton("Сохранить AGV", this);
    saveButton->setStyleSheet(
                "QPushButton {"
                "   background-color: #4CAF50;" // Цвет фона
                "   color: white;"             // Цвет текста
                "   font-size: 14px;"          // Размер шрифта
                "   padding: 10px;"            // Отступы внутри кнопки
                "}"
                "QPushButton:hover {"
                "   background-color: lightgray;" // Цвет фона при наведении
                "}"
                );
    saveButton->setFixedSize(300, 40); // Ширина 300 пикселей, высота 35 пикселей

    // Создаем горизонтальный layout для центрирования кнопки
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addStretch(); // добавляем отступ слева
    buttonLayout->addWidget(saveButton); // добавляем кнопку
    buttonLayout->addStretch(); // добавляем отступ справа

    layout->addLayout(buttonLayout); // добавляем горизонтальный layout с кнопкой в основной

    connect(saveButton, &QPushButton::clicked, this, [=]() {
        // Здесь можно добавить логику для сохранения AGV
        QString name = nameLineEdit->text();
        QString serialNumber = serialNumberLineEdit->text();
        QString fwVersion = fwVersionComboBox->currentText();
        QString model = modelLineEdit->text();
        QString documentation = documentationComboBox->currentText();

        // Логика сохранения
        // ...
        qDebug() << "Сохранено AGV:" << name << serialNumber << fwVersion << model << documentation;
    });
}
