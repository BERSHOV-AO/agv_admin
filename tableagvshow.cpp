#include "tableagvshow.h"

TableAgvShow::TableAgvShow(QWidget *parent) : QWidget(parent)
{
    db = new DataBase();
    db->connectToDataBase();

    layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(6); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Наименование" << "Серийный номер" << "Версия FW" << "Модель" << "Проектная документация" << "Дата последнего ТО");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 180);
    tableWidget->setColumnWidth(1, 180);
    tableWidget->setColumnWidth(2, 200);
    tableWidget->setColumnWidth(3, 180);
    tableWidget->setColumnWidth(4, 200);
    tableWidget->setColumnWidth(5, 180);

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

