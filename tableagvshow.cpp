#include "tableagvshow.h"

TableAgvShow::TableAgvShow(QWidget *parent) : QWidget(parent)
{
    db = new DataBase();
    db->connectToDataBase();

    layout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout();

    addAGVButton = new QPushButton("Добавить AGV", this);
    addAGVButton->setStyleSheet("background-color: #4986cf; color: white; font-size: 16px; font-family: Arial; font-weight: bold;");
    addAGVButton->setFixedSize(250, 40);
    connect(addAGVButton, &QPushButton::clicked, this, &TableAgvShow::onAddAGVClicked);

    modeEditAGV = new QPushButton("Редактор моделей AGV", this);
    modeEditAGV->setStyleSheet("background-color: #4986cf; color: white; font-size: 16px; font-family: Arial; font-weight: bold;");
    modeEditAGV->setFixedSize(250, 40);
    connect(modeEditAGV, &QPushButton::clicked, this, &TableAgvShow::onRedactorModelClicked);

    // Spacer для отталкивания кнопки к правому краю
    topLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    topLayout->addWidget(modeEditAGV);
    topLayout->addWidget(addAGVButton);
    // Добавляем горизонтальный макет в основной вертикальный макет
    layout->addLayout(topLayout);


    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(6); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Наименование" << "Серийный номер" << "Версия FW" << "Модель" << "Проектная документация" << "Дата последнего ТО");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 180);
    tableWidget->setColumnWidth(1, 180);
    tableWidget->setColumnWidth(2, 200);
    tableWidget->setColumnWidth(3, 190);
    tableWidget->setColumnWidth(4, 200);
    tableWidget->setColumnWidth(5, 200);

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, &TableAgvShow::onCellDoubleClicked);

    loadData();

    layout->addWidget(tableWidget);
    setLayout(layout);
}

void TableAgvShow::loadData() {
    // Получаем список AGV из базы данных
    // DataBase db; // Предположим, у вас есть экземпляр класса DataBase

    QList<AgvItem> agvs = db->fetchAGVs(); // Получаем данные

    // Очищаем таблицу перед загрузкой новых данных
    tableWidget->setRowCount(0);

    // Заполняем таблицу данными из списка agvs
    for (const AgvItem &agv : agvs) {
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount); // Добавляем новую строку

        tableWidget->setItem(rowCount, 0, new QTableWidgetItem(agv.getName()));
        tableWidget->setItem(rowCount, 1, new QTableWidgetItem(agv.getSerialNumber()));
        tableWidget->setItem(rowCount, 2, new QTableWidgetItem(agv.getVersionFW()));
        tableWidget->setItem(rowCount, 3, new QTableWidgetItem(agv.getModel()));
        tableWidget->setItem(rowCount, 4, new QTableWidgetItem(agv.getEPlan()));
        tableWidget->setItem(rowCount, 5, new QTableWidgetItem(formatDateFromMilliseconds(agv.getDataLastTo())));
    }
}

void TableAgvShow::onCellDoubleClicked(int row, int column) {
    if (row < 0) return; // Проверка на корректность строки

    // Получаем данные выбранного пользователя
    QString name = tableWidget->item(row, 0)->text();
    QString serialNumber = tableWidget->item(row, 1)->text();
    QString versionFW = tableWidget->item(row, 2)->text();
    QString model = tableWidget->item(row, 3)->text();
    QString ePlan = tableWidget->item(row, 4)->text();
    QString dataLastTO = tableWidget->item(row, 5)->text();

    //    AgvItem(const QString &name, const QString &serialNumber, const QString &versionFW,
    //            const QString &model, const QString &ePlan, const QString &dataLastTo);

    AgvItem selectedAGV(name, serialNumber, versionFW, model, ePlan, dataLastTO);

    TableToOneAgvShowDialog tableToOneAgvShowDialog(selectedAGV, this);
    tableToOneAgvShowDialog.resize(1200, 700);
    tableToOneAgvShowDialog.exec();

    // Открываем диалог для редактирования
    ////    AGVEditDialog editDialog(selectedAGV, this);

    // connect(&editDialog, &UserEditDialog::userDeleted, this, &UsersTableShowAndEditing::updateTable);
    // Подключаем сигнал для удаления пользователя
    //        connect(&editDialog, &UserEditDialog::userDeleted, this, [this, row]() {
    //          //  if (db->deleteUser(login)) { // Предполагается, что у вас есть метод deleteUser в DataBase
    //                tableWidget->removeRow(row); // Удаляем строку из таблицы
    //     //           qDebug() << "User deleted successfully.";
    //  //          } else {
    //    //            qDebug() << "Failed to delete user.";
    //   //         }
    //        });

    ////    if (editDialog.exec() == QDialog::Accepted) {
    //        AgvItem updatedUser = editDialog.getUser();

    //        // Обновляем данные в таблице
    //        tableWidget->item(row, 0)->setText(updatedUser.getName());
    //        tableWidget->item(row, 1)->setText(updatedUser.getSurname());
    //        tableWidget->item(row, 2)->setText(updatedUser.getLogin());
    //        tableWidget->item(row, 3)->setText(updatedUser.getPass());

    //        if (db->updateUser(login, updatedUser.getName(), updatedUser.getSurname(), updatedUser.getPass())) {
    //            qDebug() << "User updated successfully.";
    //        } else {
    //            qDebug() << "Failed to update user.";
    //        }
}
////}


void TableAgvShow::onAddAGVClicked(){

    AGVAddDialog addAGV(this);
    if (addAGV.exec() == QDialog::Accepted) {

    }
}

void TableAgvShow::onRedactorModelClicked(){

    ModelRedactorDialog redactorModel(this);
    if (redactorModel.exec() == QDialog::Accepted) {

    }
}

QString TableAgvShow::formatDateFromMilliseconds(const QString& millisecondsStr) {
    // Преобразуем строку в qint64
    bool ok;
    qint64 milliseconds = millisecondsStr.toLongLong(&ok);

    // Проверяем, успешно ли прошло преобразование
    if (!ok) {
        return QString(); // Возвращаем пустую строку в случае ошибки
    }

    // Преобразуем миллисекунды в секунды
    qint64 seconds = milliseconds / 1000;
    // Создаем объект QDateTime из секунд
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(seconds);
    // Форматируем дату и время в строку "ЧЧ:MM dd.MM.yyyy"
    return dateTime.toString("hh:mm  dd.MM.yyyy");
}
