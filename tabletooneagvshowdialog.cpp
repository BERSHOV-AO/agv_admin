#include "tabletooneagvshowdialog.h"

/**
 * statusTo - 1 ----> ТО выполнено
 * statusTo - 0 ----> TO не выполнено
 * statusTo - 2 ----> Через ~ N дней нужно выполнить TO
 */

TableToOneAgvShowDialog::TableToOneAgvShowDialog(const AgvItem &agv, QWidget *parent) : QDialog(parent), agv(agv)
{
    setWindowTitle(QString("AGV s/n: %1").arg(agv.getSerialNumber()));
    
    db = new DataBase();
    db->connectToDataBase();
    
    deleteButton = new QPushButton("Удалить AGV", this);
    deleteButton->setStyleSheet("background-color: red; color: white;");
    connect(deleteButton, &QPushButton::clicked, this, &TableToOneAgvShowDialog::oneDeleteAGVClicked);
    
    editButton = new QPushButton("Редактировать AGV", this);
    editButton->setStyleSheet("background-color: #4986cf; color: white;");
    connect(editButton, &QPushButton::clicked, this, &TableToOneAgvShowDialog::oneEditAGVClicked);
    
    layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(3); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Деталь/Наименование работ" << "Дата последнего обслуживания" << "Дата следующего обслуживания");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4986cf; color: white; }");
    
    tableWidget->setColumnWidth(0, 750);
    tableWidget->setColumnWidth(1, 200);
    tableWidget->setColumnWidth(2, 200);
    loadData();
    
    // Создаем горизонтальный layout для кнопок
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(editButton);
    
    layout->addWidget(tableWidget);
    
    // Добавляем кнопки в основной layout
    layout->addLayout(buttonLayout);
    
    setLayout(layout);
}

void TableToOneAgvShowDialog::loadData() {
    
    QList<AGVTOItem> tosOneAgv = db->fetchToOneAgv(agv.getSerialNumber()); // Получаем данные
    
    // Очищаем таблицу перед загрузкой новых данных
    tableWidget->setRowCount(0);
    
    // Заполняем таблицу данными из списка agvs
    for (const AGVTOItem &to : tosOneAgv) {
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount); // Добавляем новую строку
        
        tableWidget->setItem(rowCount, 0, new QTableWidgetItem(to.getNameTo()));
        tableWidget->setItem(rowCount, 1, new QTableWidgetItem(formatDateFromMilliseconds(to.getDataTo())));
        tableWidget->setItem(rowCount, 2, new QTableWidgetItem(addDaysToMilliseconds(to.getDataTo(), to.getFrequencyOfTo())));
        
        if (to.getStatusTo() == "1") {
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget->item(rowCount, col);
                if (item) {
                    item->setBackground(QBrush(QColor(144, 238, 144))); // Устанавливаем зеленый фон
                }
            }
        }
        
        if (to.getStatusTo() == "0") {
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget->item(rowCount, col);
                if (item) {
                    item->setBackground(QBrush(QColor(255, 182, 193))); // Светло-красный фон
                }
            }
        }
        
        if (to.getStatusTo() == "2") {
            for (int col = 0; col < tableWidget->columnCount(); ++col) {
                QTableWidgetItem *item = tableWidget->item(rowCount, col);
                if (item) {
                    item->setBackground(QBrush(Qt::yellow)); // Устанавливаем зеленый фон
                }
            }
        }
    }
}

void TableToOneAgvShowDialog::oneEditAGVClicked() {
    AGVEditDialog editDialog(agv, this);
    
    if (editDialog.exec() == QDialog::Accepted) {
        accept();
    }
}

void TableToOneAgvShowDialog::oneDeleteAGVClicked() {
    
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  QString("Вы точно хотите удалить AGV с серийным номером %1?").arg(agv.getSerialNumber()),
                                  QMessageBox::Yes | QMessageBox::No);
    
    // Проверяем, выбрал ли пользователь "Да"
    if (reply == QMessageBox::Yes) {
        // Получаем серийный номер AGV
        QString serialNumber = agv.getSerialNumber();
        
        // Сначала удаляем сам AGV
        if (db->deleteAgv(serialNumber)) {
            qDebug() << "AGV deleted successfully.";
            
            // Теперь удаляем все записи, связанные с данным AGV
            if (db->deleteAllToOneAgv(serialNumber)) {
                qDebug() << "All records related to AGV deleted successfully.";
                // emit agvDeleted(); // Сигнал для уведомления о том, что AGV был удален
                db->saveLogItem("3", "Admin", NULL, serialNumber, DELETE_AGV_STRING, QString::number(getCurrentMillisecondsSinceEpoch()));
                accept();
            } else {
                qDebug() << "Failed to delete related records for AGV.";
            }
        } else {
            qDebug() << "Failed to delete AGV.";
        }
    } else {
        qDebug() << "AGV deletion canceled.";
    }
}

QString TableToOneAgvShowDialog::formatDateFromMilliseconds(const QString& millisecondsStr) {
    // Преобразуем строку в qint64
    bool ok;
    qint64 milliseconds = millisecondsStr.toLongLong(&ok);
    
    // Проверяем, успешно ли прошло преобразование
    if (!ok) {
        return QString();
    }
    
    // Преобразуем миллисекунды в секунды
    qint64 seconds = milliseconds / 1000;
    // Создаем объект QDateTime из секунд
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(seconds);
    // Форматируем дату и время в строку "ЧЧ:MM dd.MM.yyyy"
    return dateTime.toString("hh:mm  dd.MM.yyyy");
}

QString TableToOneAgvShowDialog::addDaysToMilliseconds(const QString& millisecondsStr, const QString& daysStr) {
    // Преобразуем строку миллисекунд в qint64
    bool ok;
    qint64 milliseconds = millisecondsStr.toLongLong(&ok);
    
    // Проверяем, успешно ли прошло преобразование
    if (!ok) {
        return QString();
    }
    
    QString daysNumberStr = daysStr.split(" ")[0];
    qint64 days = daysNumberStr.toLongLong(&ok);
    
    if (!ok) {
        return QString();
    }
    
    // Преобразуем дни в миллисекунды
    qint64 millisecondsToAdd = days * 24 * 60 * 60 * 1000; // 1 день = 24 часа * 60 минут * 60 секунд * 1000 миллисекунд
    
    // Добавляем миллисекунды
    milliseconds += millisecondsToAdd;
    
    // Преобразуем миллисекунды в секунды
    qint64 seconds = milliseconds / 1000;
    
    // Создаем объект QDateTime из секунд
    QDateTime dateTime = QDateTime::fromSecsSinceEpoch(seconds);
    
    // Форматируем дату и время в строку "ЧЧ:MM dd.MM.yyyy"
    return dateTime.toString("hh:mm  dd.MM.yyyy");
}

qint64 TableToOneAgvShowDialog::getCurrentMillisecondsSinceEpoch() {
    // Получаем текущее время
    QDateTime currentDateTime = QDateTime::currentDateTime();
    
    // Преобразуем его в миллисекунды с начала эпохи
    qint64 milliseconds = currentDateTime.toMSecsSinceEpoch();
    return milliseconds;
}
