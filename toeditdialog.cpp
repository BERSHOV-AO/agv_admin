#include "toeditdialog.h"

TOEditDialog::TOEditDialog(const TOItem &toItem, const QString &nameTableModel, QWidget *parent)
    : QDialog(parent), toItem(toItem), nameTableModel(nameTableModel)
{
    setWindowTitle("Редактирование ТО");

    db = new DataBase();
    db->connectToDataBase();

    nameToEdit = new QLineEdit(toItem.getNameTo(), this);
    nameToEdit->setStyleSheet("background-color: white;");
    frequencyToEdit = new QLineEdit(toItem.getFrequencyTo(), this);
    frequencyToEdit->setStyleSheet("background-color: white;");

    QPushButton *saveButton = new QPushButton("Сохранить изменения TO", this);
    saveButton->setStyleSheet(" background-color: #4CAF50; color: white;");
    connect(saveButton, &QPushButton::clicked, this, &TOEditDialog::saveDataTo);

    deleteButton = new QPushButton("Удалить TO", this);
    deleteButton->setStyleSheet("background-color: red; color: white;");
    connect(deleteButton, &QPushButton::clicked, this, &TOEditDialog::deleteTo);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Деталь/Наименование работ", this));
    layout->addWidget(nameToEdit);
    layout->addWidget(new QLabel("Периодичность обслуживания, количество дней", this));
    layout->addWidget(frequencyToEdit);
    layout->addWidget(saveButton);
    layout->addWidget(deleteButton);

    setLayout(layout);
    setStyleSheet("background-color: #B0E0E6;");

    resize(400, 200);
}

TOItem TOEditDialog::getTo() const {
    return TOItem(nameToEdit->text(), frequencyToEdit->text());
}

void TOEditDialog::saveDataTo() {

    QString nameToStr = toItem.getNameTo();
    QString frequencyToStr = toItem.getFrequencyTo();

    qDebug() << "saveData to";

    db->updateTOSelectTable(nameTableModel, toItem.getNameTo(), toItem.getFrequencyTo(), nameToEdit->text(), frequencyToEdit->text());
    accept();
}

void TOEditDialog::deleteTo() {

    QString nameToStr = toItem.getNameTo();
    QString frequencyToStr = toItem.getFrequencyTo();

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  QString("Вы точно хотите удалить TO: %1?").arg(nameToStr),
                                  QMessageBox::Yes | QMessageBox::No);

    // Проверяем, выбрал ли пользователь "Да"
    if (reply == QMessageBox::Yes) {
        // Здесь вы можете добавить код для удаления AGV из БД
        if (db->deleteTOFromSelectModelTable(nameTableModel, nameToStr, frequencyToStr)) {
            qDebug() << "TO deleted successfully.";
            accept(); // Закрываем диалог
        } else {
            qDebug() << "Failed to delete TT.";
        }
    } else {
        qDebug() << "TO deletion canceled.";
    }
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Пример CustomMessageBox~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//QString nameToStr = toItem.getNameTo();
//QString frequencyToStr = toItem.getFrequencyTo();

//CustomMessageBox msgBox(QString("Вы точно хотите удалить TO: %1?").arg(nameToStr), this);

//if (msgBox.exec() == QDialog::Accepted) {
//    // Здесь вы можете добавить код для удаления AGV из БД
//    if (db->deleteTOFromSelectModelTable(nameTableModel, nameToStr, frequencyToStr)) {
//        qDebug() << "TO deleted successfully.";
//        accept(); // Закрываем диалог
//    } else {
//        qDebug() << "Failed to delete TT.";
//    }
//} else {
//    qDebug() << "TO deletion canceled.";
//}
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

