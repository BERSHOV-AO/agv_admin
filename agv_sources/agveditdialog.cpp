#include "agv_headers/agveditdialog.h"

AGVEditDialog::AGVEditDialog(const AgvItem &agv, QWidget *parent) : QDialog(parent), agv(agv)
{
    setWindowTitle("Редактор AGV");

    db.connectToDataBase();

    nameEdit = new QLineEdit(agv.getName(), this);
    nameEdit->setStyleSheet("background-color: white;");

    serilaNumberEdit = new QLineEdit(agv.getSerialNumber(), this);
    serilaNumberEdit->setStyleSheet("background-color: white;");

    saveButton = new QPushButton("Сохранить изменения", this);
    saveButton->setStyleSheet(" background-color: #4CAF50; color: white;");
    connect(saveButton, &QPushButton::clicked, this, &AGVEditDialog::saveData);

    //---------------------combo box FW---------------------------
    fwVersionComboBox = new QComboBox(this);
    QDir dirFW("C:/wamp64/www/host/fw");
    QStringList directoriesFW = dirFW.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
    fwVersionComboBox->setStyleSheet("QComboBox { background-color: white; }");
    //  fwVersionComboBox->setFixedSize(370, 30);
    fwVersionComboBox->addItems(directoriesFW);

    //---------------------combo box model---------------------------
    modelComboBox = new QComboBox(this);
    QList<ModelAgvItem> models = db.fetchModels();
    QStringList modelList;
    for (const ModelAgvItem& model : models) {
        modelList.append(model.getModel()); // Добавляем модель в QStringList
    }
    modelComboBox->addItems(modelList);
    modelComboBox->setStyleSheet("QComboBox { background-color: white; }");

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
    layout->addWidget(modelComboBox);
    layout->addWidget(new QLabel("Поектная документация:", this));
    layout->addWidget(documentationComboBox);
    layout->addWidget(saveButton);

    // Устанавливаем основной layout для диалога
    setLayout(layout);
    setStyleSheet("background-color: #B0E0E6;");

    resize(400, 350);
}

void AGVEditDialog::saveData() {

    QString name = nameEdit->text();
    QString serialNumber = serilaNumberEdit->text();
    QString fwVersion = fwVersionComboBox->currentText();
    QString model = modelComboBox->currentText();
    QString documentation = documentationComboBox->currentText();

    if(name.isEmpty() || serialNumber.isEmpty() || fwVersion.isEmpty() || model.isEmpty() || documentation.isEmpty()) {
        qDebug() << "Не все поля заполнены!";
        QMessageBox::warning(this, "Предупреждение", "Не все поля заполнены!");

    } else {
        // Запускаем обновление AGV в отдельном потоке
        QFuture<void> future = QtConcurrent::run([=]() {
            db.updateAgv(agv.getName(), agv.getSerialNumber(), name, serialNumber, fwVersion, model, documentation);
        });
        nameEdit->clear();
        serilaNumberEdit->clear();
        accept();
    }
}

AgvItem AGVEditDialog::getAGV(){

    return AgvItem(nameEdit->text(),
                   serilaNumberEdit->text(),
                   fwVersionComboBox->currentText(),
                   //modelEdit->text(),
                   modelComboBox->currentText(),
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
