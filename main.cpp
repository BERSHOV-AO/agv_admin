//#include "mainwindow.h"

//#include <QApplication>

//int main(int argc, char *argv[]) {
//    QApplication app(argc, argv);

//    MainWindow window; // Теперь это работает без ошибок
//    window.resize(1250, 800);
//    window.show();

//    return app.exec();
//}


#include "main_window_tables_headers/mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "database.h"
#include "entities_headers/agvtoitem.h"

#define RED_STATUS               "0"
#define YELLOW_STATUS            "2"
#define NUMBER_OF_DAYS_BEFORE_TO  5


qint64 daysToMilliseconds(int days) {
    return static_cast<qint64>(days) * 24 * 60 * 60 * 1000;
}


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    DataBase& db = DataBase::getInstance();
   // db.connectToDataBase();

   // DataBase *db = new DataBase(); // Создаем объект db

    if (!db.connectToDataBaseinFerst()) {

        QMessageBox::warning(nullptr, "Предупреждение", "Запустите Wamp Server"); // Используем nullptr
       // delete db; // Освобождаем память
        return 1; // Возвращаем 1 в случае ошибки

    }

    //-------------------------------------------------------udate status TO-------------------------------------------------------------
    QList<AGVTOItem> agvsAllTosList = db.getAllAgvTO();

    QDateTime currentDateTime = QDateTime::currentDateTime();
    qint64 currentDateTimeMilliseconds = currentDateTime.toMSecsSinceEpoch();

    for(AGVTOItem agvTo: agvsAllTosList) {

        qint64 dataToAndFrequency = agvTo.getDataTo().toLongLong() + daysToMilliseconds(agvTo.getFrequencyOfTo().toInt());
        qint64 dataToAndFrequencyMinusNumberDaysBeforeTO = dataToAndFrequency - daysToMilliseconds(NUMBER_OF_DAYS_BEFORE_TO);

        if(currentDateTimeMilliseconds > dataToAndFrequency) {
            db.updateStatusToFromAgvToTable(agvTo.getSerialNumberAGV(), agvTo.getNameTo(), RED_STATUS);
        }

        if(currentDateTimeMilliseconds < dataToAndFrequency && currentDateTimeMilliseconds > dataToAndFrequencyMinusNumberDaysBeforeTO) {
            db.updateStatusToFromAgvToTable(agvTo.getSerialNumberAGV(), agvTo.getNameTo(), YELLOW_STATUS);
        }
    }
    //-----------------------------------------------------------------------------------------------------------------------------------

    MainWindow window; // Создаем объект window
    window.resize(1250, 800);
    window.show();

   // delete db; // Освобождаем память
    return app.exec();
}




