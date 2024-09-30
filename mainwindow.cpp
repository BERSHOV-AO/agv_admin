#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    stackedWidget = new QStackedWidget(this);


    usersWidget = createUsresWidget();
    addAGVWidget = createAddAGVWidget();
    listAGVWidget = createListAGVWidget();
    logWidget = createLogWidget();


    titleLabel = new QLabel("Администрирование AGV");
    titleLabel->setStyleSheet("font-size: 28px; color: white; font-weight: bold;");

    QLabel *imageLabel = new QLabel();
    QPixmap pixmap("C:/Users/Aleksey/Documents/agv_admin/image/logo_gaz.png");
    imageLabel->setPixmap(pixmap.scaled(100, 100, Qt::KeepAspectRatio));

    line = new QFrame();
    line->setFrameShape(QFrame::HLine); // Устанавливаем форму линии
    line->setFrameShadow(QFrame::Sunken); // Устанавливаем тень для линии
    line->setLineWidth(5); // Устанавливаем ширину линии
    line->setStyleSheet("background-color: white;"); // Устанавливаем цвет

    stackedWidget->addWidget(usersWidget);
    stackedWidget->addWidget(addAGVWidget);
    stackedWidget->addWidget(listAGVWidget);
    stackedWidget->addWidget(logWidget);

    usersButton = new QPushButton("Пользователи");
    addAGVButton = new QPushButton("Добавить AGV");
    listAGVButton = new QPushButton("Список AGV");
    logButton = new QPushButton("Логи приложения");

    usersButton->setStyleSheet("background-color: white;");
    addAGVButton->setStyleSheet("background-color: white;");
    listAGVButton->setStyleSheet("background-color: white;");
    logButton->setStyleSheet("background-color: white;");

    // Подключаем кнопки к слоту переключения

    connect(usersButton, &QPushButton::clicked, this, [this]() {
        updateUsersData();
        stackedWidget->setCurrentIndex(0); // Индекс 0 - виджет добавления AGV
    });
    connect(addAGVButton, &QPushButton::clicked, this, [this]() {
        stackedWidget->setCurrentIndex(1); // Индекс 1 - виджет добавления AGV
    });
    connect(listAGVButton, &QPushButton::clicked, this, [this]() {
        updateListAGVData();
        stackedWidget->setCurrentIndex(2); // Индекс 2 - виджет списка AGV
    });
    connect(logButton, &QPushButton::clicked, this, [this]() {
        updateLogData();
        stackedWidget->setCurrentIndex(3); // Индекс 3 - виджет лога
    });

    stackedWidget->setCurrentIndex(2);

    QHBoxLayout *headerLayout = new QHBoxLayout;
    // Добавляем спейсер перед заголовком
    headerLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Заголовок по центру
    headerLayout->addWidget(titleLabel);

    // Добавляем спейсер после заголовка
    headerLayout->addSpacerItem(new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum));

    // Изображение справа
    headerLayout->addWidget(imageLabel);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(headerLayout);    // Заголовок и изображение в одном ряду
    mainLayout->addWidget(line);
    mainLayout->addWidget(stackedWidget);    // Виджеты сверху
    mainLayout->addLayout(createButtonLayout()); // Кнопки снизу

    setLayout(mainLayout);
    this->setStyleSheet("background-color: #FF1C385A;");

    setWindowTitle("AGV Management");

}

QHBoxLayout* MainWindow::createButtonLayout() {
    // Создаем горизонтальный layout для кнопок
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(usersButton);
    buttonLayout->addWidget(addAGVButton);
    buttonLayout->addWidget(listAGVButton);
    buttonLayout->addWidget(logButton);
    return buttonLayout;
}

QWidget* MainWindow::createUsresWidget() {

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    widget->setStyleSheet("background-color: lightgray;");

    layout->addWidget(new QLabel("Пользователи"));

    // Создаем и добавляем таблицу Users
    UsersTableShowAndEditing *usersTableShowAndEditing = new UsersTableShowAndEditing();
    layout->addWidget(usersTableShowAndEditing);

    widget->setLayout(layout);
    return widget;
}

QWidget* MainWindow::createAddAGVWidget() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    widget->setStyleSheet("background-color: lightgray;");

    AddAGVWidget *addAGVWidget = new AddAGVWidget();
    layout->addWidget(addAGVWidget);
    widget->setLayout(layout);
    return widget;
}

QWidget* MainWindow::createListAGVWidget() {
    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    widget->setStyleSheet("background-color: lightgray;");

    layout->addWidget(new QLabel("Список AGV"));

    // Создаем и добавляем таблицу AGV
    TableAgvShow *tableAgvShow = new TableAgvShow();
    layout->addWidget(tableAgvShow);

    widget->setLayout(layout);
    return widget;
}

QWidget* MainWindow::createLogWidget() {

    QWidget *widget = new QWidget;
    QVBoxLayout *layout = new QVBoxLayout;
    widget->setStyleSheet("background-color: lightgray;");

    layout->addWidget(new QLabel("Log AGV"));
    // Создаем и добавляем таблицу AGV
    TableLogAgvShow *tableLogAgvShow = new TableLogAgvShow();
    layout->addWidget(tableLogAgvShow);

    widget->setLayout(layout);
    return widget;
}

void MainWindow::clearStackedWidget() {
    // Удаляем все виджеты из QStackedWidget
    while (stackedWidget->count() > 0) {
        QWidget* widget = stackedWidget->widget(0); // Получаем первый виджет
        stackedWidget->removeWidget(widget); // Удаляем его из stackedWidget
        delete widget; // Освобождаем память
    }
}

void MainWindow::updateUsersData() {

    replaceWidgetAt(0, createUsresWidget());
}

void MainWindow::updateListAGVData() {

    replaceWidgetAt(2, createListAGVWidget());
}

void MainWindow::updateLogData() {

    replaceWidgetAt(3, createLogWidget());
}


void MainWindow::replaceWidgetAt(int index, QWidget* newWidget) {
    // Проверяем, что индекс валиден
    if (index >= 0 && index < stackedWidget->count()) {
        // Удаляем старый виджет
        QWidget* oldWidget = stackedWidget->widget(index);
        stackedWidget->removeWidget(oldWidget);
        delete oldWidget; // Освобождаем память

        // Добавляем новый виджет на ту же позицию
        stackedWidget->insertWidget(index, newWidget);
    }
}

MainWindow::~MainWindow()
{
}

