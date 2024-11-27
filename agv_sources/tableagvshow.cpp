#include "agv_headers/tableagvshow.h"

TableAgvShow::TableAgvShow(QWidget *parent) : QWidget(parent)
{
    db = new DataBase();
    db->connectToDataBase();

    layout = new QVBoxLayout(this);
    QHBoxLayout *topLayout = new QHBoxLayout();

    addAGVButton = new QPushButton("Добавить AGV", this);
    addAGVButton->setStyleSheet("background-color: #4986cf; color: white; font-size: 16px; font-family: Arial; font-weight: bold;");
    addAGVButton->setFixedSize(250, 35);
    connect(addAGVButton, &QPushButton::clicked, this, &TableAgvShow::onAddAGVClicked);

    // Spacer для отталкивания кнопки к правому краю
    topLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
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

    // Устанавливаем растяжение последнего столбца
    tableWidget->horizontalHeader()->setStretchLastSection(true);

    // Устанавливаем политику растягивания для всех столбцов
    for (int i = 0; i < tableWidget->columnCount(); ++i) {
        tableWidget->horizontalHeader()->setSectionResizeMode(i, QHeaderView::Stretch);
    }

    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, &TableAgvShow::onCellDoubleClicked);

    loadData();

    layout->addWidget(tableWidget);
    setLayout(layout);
}

void TableAgvShow::loadData() {

    QList<AgvItem> agvs = db->fetchAGVs(); // Получаем данные

    // Очищаем таблицу перед загрузкой новых данных
    tableWidget->setRowCount(0);

    // Заполняем таблицу данными из списка agvs
    for (AgvItem &agv : agvs) {
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount); // Добавляем новую строку

        tableWidget->setItem(rowCount, 0, new QTableWidgetItem(agv.getName()));
        tableWidget->setItem(rowCount, 1, new QTableWidgetItem(agv.getSerialNumber()));
        tableWidget->setItem(rowCount, 2, new QTableWidgetItem(agv.getVersionFW()));
        tableWidget->setItem(rowCount, 3, new QTableWidgetItem(agv.getModel()));
        tableWidget->setItem(rowCount, 4, new QTableWidgetItem(agv.getEPlan()));
        tableWidget->setItem(rowCount, 5, new QTableWidgetItem(formatDateFromMilliseconds(agv.getDataLastTo())));

        QList<AGVTOItem> tosSelectAgv = db->fetchToOneAgv(agv.getSerialNumber());

        bool foundZero = false;
        bool foundTwo = false;

        for (const AGVTOItem &to : tosSelectAgv) {
            if (to.getStatusTo() == "0") {
                foundZero = true;
                break; // Если нашли статус "0", выходим из цикла
            }
        }

        if (foundZero) {
            agv.setStatusReadyTo("0");
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget->item(rowCount, col);
                if (item) {
                    item->setBackground(QBrush(QColor(255, 182, 193))); // Светло-красный фон
                }
            }
        } else {
            // Если не нашли статус "0", проверяем на статус "2"
            for (const AGVTOItem &to : tosSelectAgv) {
                if (to.getStatusTo() == "2") {
                    foundTwo = true;
                    break; // Если нашли статус "2", выходим из цикла
                }
            }

            if (foundTwo) {
                agv.setStatusReadyTo("2");
                for (int col = 0; col < tableWidget->columnCount(); ++col) {
                    QTableWidgetItem *item = tableWidget->item(rowCount, col);
                    if (item) {
                        item->setBackground(QBrush(Qt::yellow)); // Устанавливаем желтый фон
                    }
                }
            } else {
                // Если ни статус "0", ни статус "2" не найдены
                agv.setStatusReadyTo("1");
                for (int col = 0; col < tableWidget->columnCount(); ++col) {
                    QTableWidgetItem *item = tableWidget->item(rowCount, col);
                    if (item) {
                        item->setBackground(QBrush(QColor(144, 238, 144))); // Устанавливаем зеленый фон
                    }
                }
            }
        }
        qDebug() << agv.getSerialNumber() << " : " << agv.getStatusReadyTo();
    }
}

void TableAgvShow::onCellDoubleClicked(int row) {
    if (row < 0) return; // Проверка на корректность строки

    // Получаем данные выбранного пользователя
    QString name = tableWidget->item(row, 0)->text();
    QString serialNumber = tableWidget->item(row, 1)->text();
    QString versionFW = tableWidget->item(row, 2)->text();
    QString model = tableWidget->item(row, 3)->text();
    QString ePlan = tableWidget->item(row, 4)->text();
    QString dataLastTO = tableWidget->item(row, 5)->text();

    AgvItem selectedAGV(name, serialNumber, versionFW, model, ePlan, dataLastTO);

    TableToOneAgvShowDialog tableToOneAgvShowDialog(selectedAGV, this);
    tableToOneAgvShowDialog.resize(1200, 700);
    if (tableToOneAgvShowDialog.exec() == QDialog::Accepted) {
        loadData();
        qDebug() << "Delete agv";
    }
}

void TableAgvShow::onAddAGVClicked(){

    AGVAddDialog addAGV(this);
    if (addAGV.exec() == QDialog::Accepted) {
        loadData();
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~old method~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//        if (agv.getStatusReadyTo() == "1") {
//            for (int col = 0; col < tableWidget->columnCount(); ++col) {
//                QTableWidgetItem *item = tableWidget->item(rowCount, col);
//                if (item) {
//                    item->setBackground(QBrush(QColor(144, 238, 144))); // Устанавливаем зеленый фон
//                }
//            }
//        }

//        if (agv.getStatusReadyTo() == "0") {
//            for (int col = 0; col < tableWidget->columnCount(); ++col) {
//                QTableWidgetItem *item = tableWidget->item(rowCount, col);
//                if (item) {
//                    item->setBackground(QBrush(QColor(255, 182, 193))); // Светло-красный фон
//                }
//            }
//        }

//        if (agv.getStatusReadyTo() == "2") {
//            for (int col = 0; col < tableWidget->columnCount(); ++col) {
//                QTableWidgetItem *item = tableWidget->item(rowCount, col);
//                if (item) {
//                    item->setBackground(QBrush(Qt::yellow)); // Устанавливаем зеленый фон
//                }
//            }
//        }
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
