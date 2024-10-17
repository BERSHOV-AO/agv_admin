#include "tablelogagvshow.h"

TableLogAgvShow::TableLogAgvShow(QWidget *parent) : QWidget(parent)
{
    db = new DataBase();
    db->connectToDataBase();

    layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(4); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Дата технического обслуживания" << "S/N AGV" << "Наименование ТО/Управление AGV" << "Табельный номер");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 250);
    tableWidget->setColumnWidth(1, 250);
    tableWidget->setColumnWidth(2, 370);
    tableWidget->setColumnWidth(3, 250);

    loadData();

    layout->addWidget(tableWidget);
    setLayout(layout);
}

void TableLogAgvShow::loadData() {

    QList<LogItem> logs = db->fetchLogs(); // Получаем данные

    // Очищаем таблицу перед загрузкой новых данных
    tableWidget->setRowCount(0);

    // Заполняем таблицу данными из списка agvs
    for (const LogItem &log : logs) {
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount); // Добавляем новую строку

        tableWidget->setItem(rowCount, 0, new QTableWidgetItem(formatDateFromMilliseconds(log.getTimeToAgv())));
        tableWidget->setItem(rowCount, 1, new QTableWidgetItem(log.getSerialNumberAgv()));
        tableWidget->setItem(rowCount, 2, new QTableWidgetItem(log.getNameTO()));
        tableWidget->setItem(rowCount, 3, new QTableWidgetItem(log.getTabelNum()));
    }
}

QString TableLogAgvShow::formatDateFromMilliseconds(const QString& millisecondsStr) {
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
