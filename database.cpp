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

    QString strCreateTableAgv_1100_st = "CREATE TABLE " TABLE_AGV_1100_ST " ("
                                                                          "nameTo TEXT, "
                                                                          "frequencyTo TEXT "
                                                                          ");";

    QString strCreateTableAgv_3000_st = "CREATE TABLE " TABLE_AGV_3000_ST " ("
                                                                          "nameTo TEXT, "
                                                                          "frequencyTo TEXT "
                                                                          ");";

    QString strCreateTableAgv_1100_2p = "CREATE TABLE " TABLE_AGV_1100_2P " ("
                                                                          "nameTo TEXT, "
                                                                          "frequencyTo TEXT "
                                                                          ");";

    QString strCreateTableAgv_1100_2t = "CREATE TABLE " TABLE_AGV_1100_2T " ("
                                                                          "nameTo TEXT, "
                                                                          "frequencyTo TEXT "
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

    //~~~~~~~~~~~~~~~~~~~TABLE TO AGV~~~~~~~~~~~~~~~~~~
    if (!query.exec(strCreateTableAgv_1100_st))
    {
        return false;
    }

    if (!query.exec(strCreateTableAgv_3000_st))
    {
        return false;
    }

    if (!query.exec(strCreateTableAgv_1100_2p))
    {
        return false;
    }

    if (!query.exec(strCreateTableAgv_1100_2t))
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
        UserItem user(query.value(0).toString(),
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

QList<ModelAgvItem> DataBase::fetchModels() {
    QList<ModelAgvItem> models;

    QSqlQuery query("SELECT model FROM " TABLE_MODEL);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:";
        return models;
    }

    while (query.next()) {
        ModelAgvItem model(query.value(0).toString());
        models.append(model);
    }
    return models;
}

QList<TOItem> DataBase::fetchTO(const QString nameTableTO) {
    QList<TOItem> toAGVs;

    QSqlQuery query("SELECT nameTo, frequencyTo FROM " + nameTableTO);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:";
        return toAGVs;
    }

    while (query.next()) {
        TOItem toAGV(query.value(0).toString(),
                     query.value(1).toString()
                     );
        toAGVs.append(toAGV);
    }
    return toAGVs;
}

QList<AGVTOItem> DataBase::fetchToOneAgv(const QString serialNumAGV) {
    QList<AGVTOItem> agvToItems;

    // Подготовка SQL-запроса с использованием параметра для предотвращения SQL-инъекций
    QSqlQuery query;
    query.prepare("SELECT nameTo, serialNumberAGV, frequencyOfTo, statusTo, dataTo FROM " TABLE_AGV_TO " WHERE serialNumberAGV = :serialNumAGV");
    query.bindValue(":serialNumAGV", serialNumAGV);

    if (!query.exec()) {
        qWarning() << "Ошибка выполнения запроса:"; //<< query.lastError();
        return agvToItems;
    }

    while (query.next()) {
        AGVTOItem agvToItem(
                    query.value(0).toString(), // nameTo
                    query.value(1).toString(), // serialNumberAGV
                    query.value(2).toString(), // frequencyOfTo
                    query.value(3).toString(), // statusTo
                    query.value(4).toString()  // dataTo
                    );
        agvToItems.append(agvToItem);
    }
    return agvToItems;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~save~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~


bool DataBase::saveModelItem(QString model)
{
    // Подготавливаем SQL-запрос
    QSqlQuery query(db);
    query.prepare("INSERT INTO " TABLE_MODEL " (model) "
                                             "VALUES (:model)");

    // Устанавливаем значения параметров
    query.bindValue(":model", model);

    // Выполняем запрос
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:";
        return false;
    }

    return true; // Успешное выполнение
}

bool DataBase::saveAgvTOItem(QString nameTo, QString serialNumberAGV, QString frequencyOfTo, QString statusTo, QString dataTo)
{
    // Подготавливаем SQL-запрос
    QSqlQuery query(db);
    query.prepare("INSERT INTO " TABLE_AGV_TO " (nameTo, serialNumberAGV, frequencyOfTo, statusTo, dataTo) "
                                              "VALUES (:nameTo, :serialNumberAGV, :frequencyOfTo, :statusTo, :dataTo)");

    // Устанавливаем значения параметров
    query.bindValue(":nameTo", nameTo);
    query.bindValue(":serialNumberAGV", serialNumberAGV);
    query.bindValue(":frequencyOfTo", frequencyOfTo);
    query.bindValue(":statusTo", statusTo);
    query.bindValue(":dataTo", dataTo);

    // Выполняем запрос
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:"; //<< query.lastError().text();
        return false;
    }

    return true; // Успешное выполнение
}


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

bool DataBase::saveUserItem(QString name, QString surname, QString login, QString pass)
{
    // Подготавливаем SQL-запрос
    QSqlQuery query(db);
    query.prepare("INSERT INTO " TABLE_USERS " (name, surname, login, pass) "
                                             "VALUES (:name, :surname, :login, :pass)");

    // Устанавливаем значения параметров
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);
    query.bindValue(":login", login);
    query.bindValue(":pass", pass);

    // Выполняем запрос
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:"; //<< query.lastError().text();
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

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~delete~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool DataBase::deleteUser(const QString &login, const QString &name, const QString &surname) {
    QSqlQuery query;

    // Подготовка SQL-запроса
    query.prepare("DELETE FROM " TABLE_USERS " WHERE login = :login AND name = :name AND surname = :surname");

    // Привязка параметров
    query.bindValue(":login", login);
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Error: Unable to delete user"; //<< query.lastError().text();
        return false; // Возвращаем false в случае ошибки
    }

    return true; // Возвращаем true, если все прошло успешно
}

bool DataBase::deleteAgv(const QString &serialNumber) {
    QSqlQuery query;

    // Подготовка SQL-запроса
    query.prepare("DELETE FROM " TABLE_AGV " WHERE serialNumber = :serialNumber");

    // Привязка параметра
    query.bindValue(":serialNumber", serialNumber);

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Error: Unable to delete AGV"; //<< query.lastError().text(); // Выводим текст ошибки
        return false; // Возвращаем false в случае ошибки
    }

    return true; // Возвращаем true, если все прошло успешно
}


bool DataBase::deleteAllToOneAgv(const QString serialNumAGV) {
    // Создаем SQL-запрос для удаления всех строк с заданным serialNumAGV
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE_AGV_TO " WHERE serialNumberAGV = :serialNumberAGV");
    query.bindValue(":serialNumberAGV", serialNumAGV);

    // Выполняем запрос
    if (!query.exec()) {
        // Если произошла ошибка, выводим ее в отладочный лог
        qDebug() << "Error deleting records:";//<< query.lastError().text();
        return false; // Возвращаем false в случае ошибки
    }

    return true; // Возвращаем true, если удаление прошло успешно
}


