#include "toaddfrommodeldialog.h"

ToAddFromModelDialog::ToAddFromModelDialog(
        const QString &nameTableModel,
        QWidget *parent) : QDialog(parent),
    nameTableModel(nameTableModel)
{

    setWindowTitle(QString("Добавление ТО для модели: %1").arg(nameTableModel));

    db = new DataBase();
    db->connectToDataBase();

    nameTo = new QLineEdit();
    nameTo->setStyleSheet("background-color: white;");

    frequencyTo = new QLineEdit();
    frequencyTo->setStyleSheet("background-color: white;");

    saveButton = new QPushButton("Добавить ТО", this);
    saveButton->setStyleSheet(" background-color: #4CAF50; color: white;");
    connect(saveButton, &QPushButton::clicked, this, &ToAddFromModelDialog::addTo);

    // Создаем вертикальный layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создаем лейблы и добавляем их в layout вместе с соответствующими QLineEdit

    layout->addWidget(new QLabel("Деталь/Наименование работ:", this));
    layout->addWidget(nameTo);
    layout->addWidget(new QLabel("Периодичность обслуживания, количество дней:", this));
    layout->addWidget(frequencyTo);
    layout->addWidget(saveButton);

    // Устанавливаем основной layout для диалога
    setLayout(layout);
    setStyleSheet("background-color: #B0E0E6;");

    resize(450, 200);
}

void ToAddFromModelDialog::addTo(){
    QString nameToStr = nameTo->text();
    QString frequencyToStr= frequencyTo->text();


    if(nameToStr.isEmpty() || frequencyToStr.isEmpty()) {

        qDebug() << "Не все поля заполнены!";
        QMessageBox::warning(this, "Предупреждение", "Не все поля заполнены!");

    } else {
        db->saveTOForSelectModel(nameTableModel, nameToStr, frequencyToStr);
        qDebug() << "Сохранена Модель";
        nameTo->clear();
        frequencyTo->clear();
        accept();
    }
}



