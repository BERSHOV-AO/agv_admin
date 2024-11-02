//#include "mainwindow.h"

//#include <QApplication>

//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);

//    MainWindow window; // Теперь это работает без ошибок
//    window.resize(1250, 800);
//    window.show();

//    return app.exec();
//}


#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "database.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    DataBase *db = new DataBase(); // Создаем объект db

    if (!db->connectToDataBaseinFerst()) {

        QMessageBox::warning(nullptr, "Предупреждение", "Запустите Wamp Server"); // Используем nullptr
        delete db; // Освобождаем память
        return 1; // Возвращаем 1 в случае ошибки

    }
    MainWindow window; // Создаем объект window
    window.resize(1250, 800);
    window.show();

    delete db; // Освобождаем память

    return app.exec();
}
