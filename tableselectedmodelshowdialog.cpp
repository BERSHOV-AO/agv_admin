#include "tableselectedmodelshowdialog.h"

TableSelectedModelShowDialog::TableSelectedModelShowDialog(
        const QString &nameTableModel,
        QWidget *parent) : QDialog(parent),
    nameTableModel(nameTableModel)
{

    setWindowTitle(nameTableModel);
    db = new DataBase();
    db->connectToDataBase();

    deleteButton = new QPushButton("Удалить модель", this);
    deleteButton->setStyleSheet("background-color: red; color: white;");
    connect(deleteButton, &QPushButton::clicked, this, &TableSelectedModelShowDialog::oneDeleteAGVClicked);

    addModelButton = new QPushButton("Добавить модели новое ТО", this);
    addModelButton->setStyleSheet("background-color: #4986cf; color: white;");
    connect(addModelButton, &QPushButton::clicked, this, &TableSelectedModelShowDialog::oneAddModelClicked);

    layout = new QVBoxLayout(this);
    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(2); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Деталь/Наименование работ" << "Периодичность обслуживания, количество дней"); //<< "Дата следующего обслуживания");
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 750);
    tableWidget->setColumnWidth(1, 400);
    loadData();

    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(addModelButton);

    layout->addWidget(tableWidget);

    // Добавляем кнопки в основной layout
    layout->addLayout(buttonLayout);

    setLayout(layout);
}

void TableSelectedModelShowDialog::loadData() {

    QList<TOItem> tosSelectedTable = db->fetchTO(nameTableModel); // Получаем данные

    // Очищаем таблицу перед загрузкой новых данных
    tableWidget->setRowCount(0);

    // Заполняем таблицу данными из списка agvs
    for (const TOItem &to : tosSelectedTable) {
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount); // Добавляем новую строку

        tableWidget->setItem(rowCount, 0, new QTableWidgetItem(to.getNameTo()));
        tableWidget->setItem(rowCount, 1, new QTableWidgetItem(to.getFrequencyTo()));
    }
}

void TableSelectedModelShowDialog::oneAddModelClicked() {
    ToAddFromModelDialog toAddFromModel(nameTableModel, this);

    if (toAddFromModel.exec() == QDialog::Accepted) {
        //        AgvItem updatedUser = editDialog.getUser()
    }
}

void TableSelectedModelShowDialog::oneDeleteAGVClicked() {
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Подтверждение удаления",
                                  QString("Вы точно хотите удалить модель %1?").arg(nameTableModel),
                                  QMessageBox::Yes | QMessageBox::No);

    // Проверяем, выбрал ли пользователь "Да"
    if (reply == QMessageBox::Yes) {
        // Сначала удаляем сам AGV
        if (db->dropTable(nameTableModel)) {
            qDebug() << "AGV deleted successfully.";

            // Теперь удаляем модель
            if (db->deleteModel(nameTableModel)) {
                qDebug() << "Model deleted successfully.";
                accept(); // Закрываем диалог
            } else {
                qDebug() << "Failed to delete model.";
                QMessageBox::warning(this, "Error", "Ошибка при удалении модели");
            }
        } else {
            qDebug() << "Failed to delete AGV.";
            QMessageBox::warning(this, "Error", "Ошибка при удалении AGV");
        }
    } else {
        qDebug() << "AGV deletion canceled.";
    }
}
