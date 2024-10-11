#include "modelredactordialog.h"

ModelRedactorWidget::ModelRedactorWidget(QWidget *parent) : QWidget(parent)
{

    setWindowTitle("Редактор моделей AGV");

    db = new DataBase();
    db->connectToDataBase();

    layout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout();

    addModelButton = new QPushButton("Добавить модель AGV", this);
    addModelButton->setStyleSheet("background-color: #4986cf; color: white; font-size: 16px; font-family: Arial; font-weight: bold;");
    addModelButton->setFixedSize(250, 35);
    connect(addModelButton, &QPushButton::clicked, this, &ModelRedactorWidget::onAddModelClicked);

    //   Spacer для отталкивания кнопки к правому краю
    topLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    topLayout->addWidget(addModelButton);
    // Добавляем горизонтальный макет в основной вертикальный макет
    layout->addLayout(topLayout);

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(1); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Модель" );
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 1200);

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    //    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, &UsersTableShowAndEditing::onCellDoubleClicked);

    loadData();

    layout->addWidget(tableWidget);
    setLayout(layout);
}


void ModelRedactorWidget::loadData() {
    // Получаем список AGV из базы данных
    // DataBase db; // Предположим, у вас есть экземпляр класса DataBase

    QList<ModelAgvItem> models = db->fetchModels(); // Получаем данные

    // Очищаем таблицу перед загрузкой новых данных
    tableWidget->setRowCount(0);

    // Заполняем таблицу данными из списка agvs
    for (const ModelAgvItem &model : models) {
        int rowCount = tableWidget->rowCount();
        tableWidget->insertRow(rowCount); // Добавляем новую строку

        tableWidget->setItem(rowCount, 0, new QTableWidgetItem(model.getModel()));
    }
}


//void ModelRedactorWidget::onCellDoubleClicked(int row, int column) {
//    if (row < 0) return; // Проверка на корректность строки

//    // Получаем данные выбранного пользователя
//    QString model = tableWidget->item(row, 0)->text();
////    QString serialNumber = tableWidget->item(row, 1)->text();
////    QString versionFW = tableWidget->item(row, 2)->text();
////    QString model = tableWidget->item(row, 3)->text();
////    QString ePlan = tableWidget->item(row, 4)->text();
////    QString dataLastTO = tableWidget->item(row, 5)->text();

////    AgvItem selectedAGV(name, serialNumber, versionFW, model, ePlan, dataLastTO);

//    TableToOneAgvShowDialog tableToOneAgvShowDialog(selectedAGV, this);
//    tableToOneAgvShowDialog.resize(1200, 700);
//    tableToOneAgvShowDialog.exec();
//}

void ModelRedactorWidget::onAddModelClicked() {



    ModelAddDialog addModelDialog(this);
    if (addModelDialog.exec() == QDialog::Accepted) {

    }
}
