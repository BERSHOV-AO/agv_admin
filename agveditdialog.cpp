#include "agveditdialog.h"

AGVEditDialog::AGVEditDialog(const AgvItem &agv, QWidget *parent) : QDialog(parent), agv(agv)
{
    setWindowTitle("Редактор AGV");

    db = new DataBase();
    db->connectToDataBase();

    nameEdit = new QLineEdit(agv.getName(), this);
    nameEdit->setStyleSheet("background-color: white;");

    serilaNumberEdit = new QLineEdit(agv.getSerialNumber(), this);
    serilaNumberEdit->setStyleSheet("background-color: white;");

    //    fwVersionEdit = new QLineEdit();
    //    fwVersionEdit->setStyleSheet("background-color: white;");

    modelEdit = new QLineEdit(agv.getModel(), this);
    modelEdit->setStyleSheet("background-color: white;");

    //    projectDocumentationEdit = new QLineEdit();
    //    projectDocumentationEdit->setStyleSheet("background-color: white;");

    saveButton = new QPushButton("Сохранить изменения", this);
    saveButton->setStyleSheet(" background-color: #4CAF50; color: white;");
    connect(saveButton, &QPushButton::clicked, this, &AGVEditDialog::saveData);

    //---------------------combo box FW---------------------------
    fwVersionComboBox = new QComboBox(this);
    // fwVersionComboBox->setFixedSize(300, 30);
    // Получаем список директорий
    QDir dirFW("C:/wamp64/www/host/fw");
    QStringList directoriesFW = dirFW.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    fwVersionComboBox->setStyleSheet("QComboBox { background-color: white; }");
    //  fwVersionComboBox->setFixedSize(370, 30);
    fwVersionComboBox->addItems(directoriesFW);

    //---------------------combo box sPlan---------------------------
    documentationComboBox = new QComboBox(this);
    //  documentationComboBox->setFixedSize(340, 25);
    // Получаем список директорий
    QDir dir("C:/wamp64/www/host/schemes");
    QStringList directories = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    documentationComboBox->setStyleSheet("QComboBox { background-color: white; }");
    documentationComboBox->addItems(directories);
    //----------------------------------------------------------

    // Создаем вертикальный layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создаем лейблы и добавляем их в layout вместе с соответствующими QLineEdit
    layout->addWidget(new QLabel("Наименование:", this));
    layout->addWidget(nameEdit);
    layout->addWidget(new QLabel("Серийный номер:", this));
    layout->addWidget(serilaNumberEdit);
    layout->addWidget(new QLabel("Версия FW:", this));
    layout->addWidget(fwVersionComboBox);
    layout->addWidget(new QLabel("Модель:", this));
    layout->addWidget(modelEdit);
    layout->addWidget(new QLabel("Поектная документация:", this));
    layout->addWidget(documentationComboBox);
    layout->addWidget(saveButton);

    // Устанавливаем основной layout для диалога
    setLayout(layout);
    setStyleSheet("background-color: #B0E0E6;");

    resize(400, 350);
}

void AGVEditDialog::saveData() {

}

void AGVEditDialog::deleteAGV() {

}

AgvItem AGVEditDialog::getAGV(){

    return AgvItem(nameEdit->text(),
                   serilaNumberEdit->text(),
                   fwVersionComboBox->currentText(),
                   modelEdit->text(),
                   documentationComboBox->currentText(),
                   QString::number(getCurrentMillisecondsSinceEpoch()));
}

qint64 AGVEditDialog::getCurrentMillisecondsSinceEpoch() {
    // Получаем текущее время
    QDateTime currentDateTime = QDateTime::currentDateTime();

    // Преобразуем его в миллисекунды с начала эпохи
    qint64 milliseconds = currentDateTime.toMSecsSinceEpoch();
    return milliseconds;
}



