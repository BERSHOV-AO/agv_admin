#include "modelredactordialog.h"

ModelRedactorDialog::ModelRedactorDialog(QWidget *parent) : QDialog(parent)
{

    setWindowTitle("Редактор моделей AGV");

    db = new DataBase();
    db->connectToDataBase();

    layout = new QVBoxLayout(this);

    QHBoxLayout *topLayout = new QHBoxLayout();

    addModelButton = new QPushButton("Добавить модель", this);
    addModelButton->setStyleSheet("background-color: #4986cf; color: white;");
    //  addModelButton->setFixedSize(250, 40);
    connect(addModelButton, &QPushButton::clicked, this, &ModelRedactorDialog::onAddModelClicked);

    // Spacer для отталкивания кнопки к правому краю
    //    topLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));
    //    topLayout->addWidget(addModelButton);
    //    // Добавляем горизонтальный макет в основной вертикальный макет
    //    layout->addLayout(topLayout);

    tableWidget = new QTableWidget(this);
    tableWidget->setColumnCount(1); // Например, 3 колонки: ID, Название, Статус
    tableWidget->setHorizontalHeaderLabels(QStringList() << "Модель" );
    tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section { background-color: #4CAF50; color: white; }");

    tableWidget->setColumnWidth(0, 450);

    tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    //    connect(tableWidget, &QTableWidget::cellDoubleClicked, this, &UsersTableShowAndEditing::onCellDoubleClicked);

    loadData();

    layout->addWidget(tableWidget);
    layout->addWidget(addModelButton);
    setLayout(layout);
    resize(450, 400);
}


void ModelRedactorDialog::loadData() {
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

void ModelRedactorDialog::onAddModelClicked() {



        ModelAddDialog addModelDialog(this);
        if (addModelDialog.exec() == QDialog::Accepted) {

        }
}
