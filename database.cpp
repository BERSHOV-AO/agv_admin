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

                                                              "name TEXT, "
                                                              "surname TEXT, "
                                                              "login TEXT, "
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


//-------------------------------------------------------------fetch----------------------------------------------------------------
QList<AgvItem> DataBase::fetchAGVs() {
    QList<AgvItem> agvs;

    QSqlQuery query("SELECT name, serialNumber, versionFW, model, ePlan, dataLastTo FROM " TABLE_AGV);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:";
        return agvs;
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

QList<UserItem> DataBase::fetchUsers() {
    QList<UserItem> users;

    QSqlQuery query("SELECT name, surname, login, pass FROM " TABLE_USERS);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:";
        return users;
    }

    while (query.next()) {
        UserItem user(
                    query.value(0).toString(),
                    query.value(1).toString(),
                    query.value(2).toString(),
                    query.value(3).toString()
                    );
        users.append(user);
    }

    return users;
}

QList<LogItem> DataBase::fetchLogs() {
    QList<LogItem> logs;

    QSqlQuery query("SELECT typeLog, tabelNum, timeOpenApp, serialNumberAgv, nameTO, timeToAgv FROM " TABLE_LOG);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:";
        return logs; // Возвращаем пустой список в случае ошибки
    }

    while (query.next()) {
        LogItem log(
                    query.value(0).toString(),
                    query.value(1).toString(),
                    query.value(2).toString(),
                    query.value(3).toString(),
                    query.value(4).toString(),
                    query.value(5).toString()
                    );
        logs.append(log);
    }

    return logs;
}

//-------------------------------------------------------------------------------------------------------------------------------

bool DataBase::saveAgvItem(QString name, QString serialNumber, QString versionFW, QString model, QString ePlan, QString dataLastTo)
{

    // Подготавливаем SQL-запрос
    QSqlQuery query(db);
    query.prepare("INSERT INTO " TABLE_AGV " (name, serialNumber, versionFW, model, ePlan, dataLastTo) "
                                           "VALUES (:name, :serialNumber, :versionFW, :model, :ePlan, :dataLastTo)");

    // Устанавливаем значения параметров
    query.bindValue(":name", name);
    query.bindValue(":serialNumber", serialNumber);
    query.bindValue(":versionFW", versionFW);
    query.bindValue(":model", model);
    query.bindValue(":ePlan", ePlan);
    query.bindValue(":dataLastTo", dataLastTo);

    // Выполняем запрос
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:"; //<< query.lastError().text();
        return false;
    }

    return true; // Успешное выполнение
}



//tabelNum - табельный номер
//--------------------------------
// typeLog
// 1 - тип log вход в app
// 2 - тип log время выполнения TO
// 3 - тип log добавления agv
//---------------------------------

bool DataBase::saveLogItem(QString typeLog, QString tabelNum, QString timeOpenApp, QString serialNumberAgv, QString nameTO, QString timeToAgv)
{
    // Подготавливаем SQL-запрос
    QSqlQuery query(db);
    query.prepare("INSERT INTO " TABLE_LOG " (typeLog, tabelNum, timeOpenApp, serialNumberAgv, nameTO, timeToAgv) "
                                           "VALUES (:typeLog, :tabelNum, :timeOpenApp, :serialNumberAgv, :nameTO, :timeToAgv)");
    // Устанавливаем значения параметров
    query.bindValue(":typeLog", typeLog);
    query.bindValue(":tabelNum", tabelNum);
    query.bindValue(":timeOpenApp", timeOpenApp);
    query.bindValue(":serialNumberAgv", serialNumberAgv);
    query.bindValue(":nameTO", nameTO);
    query.bindValue(":timeToAgv", timeToAgv);

    // Выполняем запрос
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:";
        return false;
    }
    return true; // Успешное выполнение
}

bool DataBase::updateUser(const QString &login, const QString &newName, const QString &newSurname, const QString &newPass) {
    QSqlQuery query;

    // Подготовка SQL-запроса
    query.prepare("UPDATE " TABLE_USERS " SET name = :name, surname = :surname, pass = :pass WHERE login = :login");

    // Привязка параметров
    query.bindValue(":name", newName);
    query.bindValue(":surname", newSurname);
    query.bindValue(":pass", newPass);
    query.bindValue(":login", login);

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Error: Unable to update user"; //<< query.lastError().text();
        return false; // Возвращаем false в случае ошибки
    }

    return true; // Возвращаем true, если все прошло успешно
}

