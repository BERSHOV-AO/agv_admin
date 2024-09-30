#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow window; // Теперь это работает без ошибок
    window.resize(1250, 800);
    window.show();

    return app.exec();
}
