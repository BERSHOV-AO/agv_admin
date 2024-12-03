#include "modeladddialog.h"

ModelAddDialog::ModelAddDialog(QWidget *parent) : QDialog(parent)
{

    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~Dafault~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    mapDafaultTO["Корпус - очистка от загрязнений"] = "30";
    mapDafaultTO["Корпус - контроль резьбовых соединений, протяжка"] = "30";
    mapDafaultTO["Позиционирующие ролики - проверить на наличие люфтов"] = "30";

    mapDafaultTO["Сканер безопасности - очистка сканера безопасности"] = "30";
    mapDafaultTO["Сканер безопасности - проверка крепления кабеля сканера"] = "30";

    mapDafaultTO["Бампер - контроль резьбовых соединений, протяжка"] = "30";
    mapDafaultTO["Лицевая панель - контроль целостности защиты панели"] = "30";

    mapDafaultTO["Электрика - проверка работы звука"] = "30";
    mapDafaultTO["Электрика - Контроль целостности кнопок и панели"] = "30";

    mapDafaultTO["PIN - Очистка (c разборкой)"] = "90";
    mapDafaultTO["PIN - Контроль резбовых соединений, протяжка"] = "30";
    mapDafaultTO["PIN - Осмотр, контроль люфтов"] = "30";
    mapDafaultTO["PIN - Проверить укладку проводов"] = "30";
    mapDafaultTO["PIN - Проверить работу"] = "30";
    mapDafaultTO["PIN - Контроль верхнего положения -> max 3мм. не доходит"] = "30";
    mapDafaultTO["PIN - Смазка"] = "30";

    mapDafaultTO["Подъемник - Проверить устан. штифты на кулачке"] = "30";
    mapDafaultTO["Подъемник - Контроль резбовых соединений, протяжка"] = "30";
    mapDafaultTO["Подъемник - Проверить крепление опорных подшипников"] = "30";
    mapDafaultTO["Подъемник - Проверить работу подъемника"] = "30";
    mapDafaultTO["Подъемник - Проверка срабат. концевиков (настройка)"] = "30";

    mapDafaultTO["Drive unit - Проверить крепление поъемной втулки"] = "30";
    mapDafaultTO["Drive unit - Контроль резбовых соединений, протяжка"] = "30";
    mapDafaultTO["Drive unit - Проверка укладки и целостности кабеля"] = "30";
    mapDafaultTO["Drive unit - Осмотр контроль люфтов"] = "30";
    mapDafaultTO["Drive unit - Контроль натяжения цепей"] = "90";
    mapDafaultTO["Drive unit - Смазка цепей"] = "30";

    mapDafaultTO["Датчик трека и RFID - Проверить крепление"] = "30";
    mapDafaultTO["Датчик трека и RFID - Проверить целостность"] = "30";
    mapDafaultTO["Датчик трека и RFID - Проверить целостность и укладку кабелей"] = "30";
    mapDafaultTO["Датчик трека и RFID - Проверить крепление и наличие защиты"] = "30";
    mapDafaultTO["Датчик трека и RFID - Высота от пола -> не более 20 мм."] = "30";

    mapDafaultTO["Колеса приводные - Контроль диаметра наружного -> min Ø 145"] = "30";
    mapDafaultTO["Колеса приводные - Проверить продольный люфт"] = "30";
    mapDafaultTO["Колеса приводные - Проверить крепление крышки колеса -> до упора, с LOCTITE 243"] = "30";

    mapDafaultTO["Приводные звездочки - Очистка от мусора"] = "30";
    mapDafaultTO["Приводные звездочки - Проверить устан. штифты на звездах"] = "30";
    mapDafaultTO["Приводные звездочки - Проверить крепление крышки звездочки -> до упора, с LOCTITE 243"] = "30";

    mapDafaultTO["Колеса поворотные - Очистка от загрязнений"] = "30";
    mapDafaultTO["Колеса поворотные - Проверить продольный люфт"] = "30";

    mapDafaultTO["Колеса задние - Проверить продольный люфт"] = "30";
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    setWindowTitle("Добавление модели");
    db.connectToDataBase();

    modelEdit = new QLineEdit();
    modelEdit->setStyleSheet("background-color: white;");

    saveButton = new QPushButton("Добавить модель", this);
    saveButton->setStyleSheet(" background-color: #4CAF50; color: white;");
    connect(saveButton, &QPushButton::clicked, this, &ModelAddDialog::addModel);

    defaultCheckBox = new QCheckBox("Создать список ТО по умолчанию", this);

    // Создаем вертикальный layout
    QVBoxLayout *layout = new QVBoxLayout(this);

    // Создаем лейблы и добавляем их в layout вместе с соответствующими QLineEdit

    layout->addWidget(new QLabel("Модель:", this));
    layout->addWidget(modelEdit);
    layout->addWidget(defaultCheckBox); // Добавляем чекбокс в layout
    layout->addWidget(saveButton);

    // Устанавливаем основной layout для диалога
    setLayout(layout);
    setStyleSheet("background-color: #B0E0E6;");

    resize(300, 140);
}

void ModelAddDialog::addModel() {

    QString model = modelEdit->text();

    if(model.isEmpty()) {

        qDebug() << "Не все поля заполнены!";
        QMessageBox::warning(this, "Предупреждение", "Заполните название модели!");

    } else {
        bool isDefaultCheckBox = defaultCheckBox->isChecked();

        if(db.createNewModelTable(model)) {
            db.saveModelItem(model);

            if(isDefaultCheckBox) {

                for (const auto &key : mapDafaultTO.keys()) {

                    db.saveTOForSelectModel(model, key, mapDafaultTO.value(key));
                }
            }
            qDebug() << "Сохранена модель:";
            accept();

        } else {
            qDebug() << "Модель не создана!";
            modelEdit->clear();
            QMessageBox::warning(this, "Предупреждение", "Название модели длжно быть формата (AGV_1100_ST)!");
        }
    }
}
