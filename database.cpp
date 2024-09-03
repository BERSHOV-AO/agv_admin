#include "database.h"

/*
INSERT INTO TABLE_AGV (name, serialNumber, versionFW, model, ePlan, dataLastTo)
VALUES ('AGV1', '123456', '1.0', 'ModelX', 'ePlan1', '2023-10-01');

*******************************************************************************
*******************************************************************************

INSERT INTO TABLE_AGV (name, serialNumber, versionFW, model, ePlan, dataLastTo)
VALUES
    ('AGV1', 'SN123456', '1.0', 'ModelX', 'ePlan1', '2023-10-01'),
    ('AGV2', 'SN123457', '1.1', 'ModelY', 'ePlan2', '2023-10-02'),
    ('AGV3', 'SN123458', '1.2', 'ModelZ', 'ePlan3', '2023-10-03');

*/

DataBase::DataBase(QObject *parent) : QObject(parent)
{

}


void DataBase::connectToDataBase()
{
    /* Перед подключением к базе данных производим проверку на её существование.
     * В зависимости от результата производим открытие базы данных или её восстановление
     * */

    if(!QFile(DIR_AND_NAME_DATABASE).exists())
    {
        restoreDataBase();
    }
    else
    {
        openDataBase();
    }
}

/* Методы восстановления базы данных */
bool DataBase::restoreDataBase()
{
    // Если база данных открылась …

    if(openDataBase())
    {
        return (createTable()) ? true : false; // Создаем новую базу данных
    }
    else
    {
        return false;
    }
    return false;
}

/* Метод для открытия базы данных */
bool DataBase::openDataBase()
{
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */

    db = QSqlDatabase::addDatabase("QSQLITE");
    //db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DIR_AND_NAME_DATABASE);
    //db.setDatabaseName("./dirDB/dbLogbook.db");

    if(db.open())
    {
        return true;
    }
    else
    {
        return false;
    }
}

/* Методы закрытия базы данных */
bool DataBase::closeDataBase()
{
    db.close();
    return true;
}

/* Метод для создания таблицы в базе данных */
bool DataBase::createTable()
{
    QSqlQuery query;

    QString strCreateTableUsers = "CREATE TABLE " TABLE_USERS " ("
                                                              "login TEXT, "
                                                              "email TEXT, "
                                                              "pass TEXT "
                                                              ");";

    QString strCreateTableLog = "CREATE TABLE " TABLE_LOG " ("
                                                          "typeLog TEXT, "
                                                          "tabelNum TEXT, "
                                                          "timeOpenApp TEXT, "
                                                          "serialNumberAgv TEXT, "
                                                          "nameTO TEXT, "
                                                          "timeToAgv TEXT "
                                                          ");";

    QString strCreateTableAgv = "CREATE TABLE " TABLE_AGV " ("
                                                          "name TEXT, "
                                                          "serialNumber TEXT, "
                                                          "versionFW TEXT, "
                                                          "model TEXT, "
                                                          "ePlan TEXT, "
                                                          "dataLastTo TEXT "
                                                          ");";

    QString strCreateTableAgvTo = "CREATE TABLE " TABLE_AGV_TO " ("
                                                               "nameTo TEXT, "
                                                               "serialNumberAGV TEXT, "
                                                               "frequencyOfTo TEXT, "
                                                               "statusTo TEXT, "
                                                               "dataTo TEXT "
                                                               ");";

    QString strCreateTableModel = "CREATE TABLE " TABLE_MODEL " ("
                                                              "model TEXT "
                                                              ");";

    if (!query.exec(strCreateTableUsers))
    {
        return false;
    }

    if (!query.exec(strCreateTableLog))
    {
        return false;
    }

    if (!query.exec(strCreateTableAgv))
    {
        return false;
    }

    if (!query.exec(strCreateTableAgvTo))
    {
        return false;
    }

    if (!query.exec(strCreateTableModel))
    {
        return false;
    }

    return true;
}


QList<AgvItem> DataBase::fetchAGVs() {
    QList<AgvItem> agvs;

    QSqlQuery query("SELECT name, serialNumber, versionFW, model, ePlan, dataLastTo FROM " TABLE_AGV);

    if (!query.exec()) {
     //   qWarning() << "Ошибка выполнения запроса:" << query.lastError().text();
        return agvs; // Возвращаем пустой список в случае ошибки
    }

    while (query.next()) {
        AgvItem agv(
            query.value(0).toString(),
            query.value(1).toString(),
            query.value(2).toString(),
            query.value(3).toString(),
            query.value(4).toString(),
            query.value(5).toString()
        );
        agvs.append(agv);
    }

    return agvs;
}

