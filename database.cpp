#include "database.h"

DataBase::DataBase(QObject *parent) : QObject(parent)
{
    readIpAddress = readIpFromFile();
}

DataBase& DataBase::getInstance() {
    static DataBase instance;
    return instance;
}


bool DataBase::connectToDataBaseinFerst()
{
    QSqlDatabase dbConnect = QSqlDatabase::addDatabase("QMYSQL");
    dbConnect.setHostName(readIpAddress);
    if(readIpAddress == HOST_NAME) {
        dbConnect.setUserName(USER_NAME);
    } else {
       dbConnect.setUserName("ale");
    }
    dbConnect.setDatabaseName(DATABASE_NAME);


    if (!dbConnect.open()) {
        QSqlError error = dbConnect.lastError();
               qDebug() << "Error connecting to database: " << error.text(); // Сообщение об ошибке
               qDebug() << "Error code: " << error.number(); // Код ошибки

       //  qDebug() << dbConnect;
       // qDebug() << "Error connecting to database: ";
        return false;
    }
    return true;
}

//bool DataBase::connectToDataBase()
//{
//    QSqlDatabase dbConnect = QSqlDatabase::addDatabase("QMYSQL");
//    dbConnect.setHostName(HOST_NAME);
//    dbConnect.setUserName(USER_NAME);
//    dbConnect.setDatabaseName(DATABASE_NAME);

//    if (!dbConnect.open()) {
//        qDebug() << "Error connecting to database: ";
//        return false;
//    }
//    db = dbConnect;
//    if(!hasTables()) {
//        createTable();
//    }

//    return true;
//}

bool DataBase::connectToDataBase() {
    // Проверяем, существует ли уже соединение с базой данных
    if (QSqlDatabase::contains("myConnection")) {
        db = QSqlDatabase::database("myConnection");
        if (db.isOpen()) {
            qDebug() << "Using existing database connection.";
            return true; // Соединение уже открыто
        } else {
            qDebug() << "Existing connection found but it is not open.";
        }
    }

    // Создаем новое соединение
    QSqlDatabase dbConnect = QSqlDatabase::addDatabase("QMYSQL", "myConnection");
    dbConnect.setHostName(readIpAddress);
    if(readIpAddress == HOST_NAME) {
        dbConnect.setUserName(USER_NAME);
    } else {
       dbConnect.setUserName("ale");
    }
    dbConnect.setDatabaseName(DATABASE_NAME);

    if (!dbConnect.open()) {
        QSqlError error = dbConnect.lastError();
               qDebug() << "Error connecting to database: " << error.text(); // Сообщение об ошибке
               qDebug() << "Error code: " << error.number(); // Код ошибки
       // qDebug() << "Error connecting to database: ";
        return false;
    }

    db = dbConnect;

    if (!hasTables()) {
        createTable();
    }
    return true;
}


/* Метод для создания таблицы в базе данных */
bool DataBase::createTable()
{
    QSqlQuery query;

    QString strCreateTableUsers = "CREATE TABLE " TABLE_USERS " ("
                                                              "id INT AUTO_INCREMENT PRIMARY KEY, "
                                                              "name TEXT, "
                                                              "surname TEXT, "
                                                              "login TEXT, "
                                                              "pass TEXT "
                                                              ");";

    QString strCreateTableLog = "CREATE TABLE " TABLE_LOG " ("
                                                          "id INT AUTO_INCREMENT PRIMARY KEY, "
                                                          "typeLog TEXT, "
                                                          "tabelNum TEXT, "
                                                          "timeOpenApp TEXT, "
                                                          "serialNumberAgv TEXT, "
                                                          "nameTO TEXT, "
                                                          "timeToAgv TEXT "
                                                          ");";

    QString strCreateTableAgv = "CREATE TABLE " TABLE_AGV " ("
                                                          "id INT AUTO_INCREMENT PRIMARY KEY, "
                                                          "name TEXT, "
                                                          "serialNumber TEXT, "
                                                          "versionFW TEXT, "
                                                          "model TEXT, "
                                                          "ePlan TEXT, "
                                                          "dataLastTo TEXT "
                                                          ");";

    QString strCreateTableAgvTo = "CREATE TABLE " TABLE_AGV_TO " ("
                                                               "id INT AUTO_INCREMENT PRIMARY KEY, "
                                                               "nameTo TEXT, "
                                                               "serialNumberAGV TEXT, "
                                                               "frequencyOfTo TEXT, "
                                                               "statusTo TEXT, "
                                                               "dataTo TEXT "
                                                               ");";

    QString strCreateTableModel = "CREATE TABLE " TABLE_MODEL " ("
                                                              "id INT AUTO_INCREMENT PRIMARY KEY, "
                                                              "model TEXT "
                                                              ");";

    //    QString strCreateTableAgv_1100_st = "CREATE TABLE " TABLE_AGV_1100_ST " ("
    //                                                                          "nameTo TEXT, "
    //                                                                          "frequencyTo TEXT "
    //                                                                          ");";

    //    QString strCreateTableAgv_3000_st = "CREATE TABLE " TABLE_AGV_3000_ST " ("
    //                                                                          "nameTo TEXT, "
    //                                                                          "frequencyTo TEXT "
    //                                                                          ");";

    //    QString strCreateTableAgv_1100_2p = "CREATE TABLE " TABLE_AGV_1100_2P " ("
    //                                                                          "nameTo TEXT, "
    //                                                                          "frequencyTo TEXT "
    //                                                                          ");";

    //    QString strCreateTableAgv_1100_2t = "CREATE TABLE " TABLE_AGV_1100_2T " ("
    //                                                                          "nameTo TEXT, "
    //                                                                          "frequencyTo TEXT "
    //                                                                          ");";
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

bool DataBase::hasTables() {
    if (db.isOpen()) {
        QSqlQuery query(db);
        if (query.exec("SELECT name FROM sqlite_master WHERE type='table'")) {
            return query.next();
        }
    }
    return false;
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
    //~~~~~~~~~~~~~~~~db local~~~~~~~~~~~~~~~~~~~~~~~~~
    /* База данных открывается по заданному пути
     * и имени базы данных, если она существует
     * */
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DIR_AND_NAME_DATABASE);
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    //~~~~~~~~~~~~~remote db~~~~~~~~~~~~~~~~~~
    //    db = QSqlDatabase::addDatabase("QMYSQL");
    //    db.setHostName("localhost");
    //    //db.setDatabaseName("agv_db");
    //    db.setDatabaseName(DATABASE_NAME);
    //    db.setUserName("root");
    //~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

//------------------------------------------------------------create---------------------------------------------------------------

bool DataBase::createNewModelTable(const QString tableName) {
    QSqlQuery query;

    QString strCreateTableNewModel = "CREATE TABLE " + tableName + " ("
                                                                   "id INT AUTO_INCREMENT PRIMARY KEY, "
                                                                   "nameTo TEXT, "
                                                                   "frequencyTo TEXT "
                                                                   ");";
    if (!query.exec(strCreateTableNewModel))
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
        return logs;
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
        qWarning() << "Ошибка выполнения запроса:";
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

QList<AGVTOItem> DataBase::getAllAgvTO() {
    QList<AGVTOItem> agvToList;

    // SQL-запрос для выборки всех записей из таблицы AGV_TO без id
    QString strSelectAgvTo = "SELECT nameTo, serialNumberAGV, frequencyOfTo, statusTo, dataTo FROM " TABLE_AGV_TO;

    QSqlQuery query;
    if (!query.exec(strSelectAgvTo)) {
        qWarning() << "Ошибка выполнения запроса:";
        return agvToList; // Возвращаем пустой список в случае ошибки
    }

    // Обработка результатов запроса
    while (query.next()) {
        QString nameToStr = query.value("nameTo").toString();
        QString serialNumberAGVStr = query.value("serialNumberAGV").toString();
        QString frequencyOfToStr = query.value("frequencyOfTo").toString();
        QString statusToStr = query.value("statusTo").toString();
        QString dataToStr = query.value("dataTo").toString();

        agvToList.append(AGVTOItem(nameToStr, serialNumberAGVStr, frequencyOfToStr, statusToStr, dataToStr));
    }
    return agvToList;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~save~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool DataBase::saveTOForSelectModel(const QString nameTableModel, const QString nameTo, const QString frequencyTo) {
    // Подготавливаем SQL-запрос
    QSqlQuery query(db);

    // Формируем SQL-запрос для вставки данных
    QString sql = QString("INSERT INTO %1 (nameTo, frequencyTo) VALUES (:nameTo, :frequencyTo)").arg(nameTableModel);

    // Подготовка запроса
    query.prepare(sql);

    // Привязываем значения к параметрам
    query.bindValue(":nameTo", nameTo);
    query.bindValue(":frequencyTo", frequencyTo);

    // Выполняем запрос и проверяем успешность выполнения
    if (!query.exec()) {
        qDebug() << "Ошибка при сохранении данных:";
        return false;
    }

    return true;
}



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
        qDebug() << "Ошибка выполнения запроса:";
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
        qDebug() << "Ошибка выполнения запроса:";
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
        qDebug() << "Ошибка выполнения запроса:";
        return false;
    }

    return true; // Успешное выполнение
}


//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~delete~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool DataBase::deleteUser(const QString &login, const QString &name, const QString &surname) {
    QMutexLocker locker(&mutex);
    QSqlQuery query;

    // Подготовка SQL-запроса
    query.prepare("DELETE FROM " TABLE_USERS " WHERE login = :login AND name = :name AND surname = :surname");

    // Привязка параметров
    query.bindValue(":login", login);
    query.bindValue(":name", name);
    query.bindValue(":surname", surname);

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Error: Unable to delete user";
        return false;
    }

    return true;
}

bool DataBase::deleteAgv(const QString &serialNumber) {
    QSqlQuery query;

    // Подготовка SQL-запроса
    query.prepare("DELETE FROM " TABLE_AGV " WHERE serialNumber = :serialNumber");

    // Привязка параметра
    query.bindValue(":serialNumber", serialNumber);

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Error: Unable to delete AGV";
        return false;
    }

    return true;
}


bool DataBase::deleteAllToOneAgv(const QString serialNumAGV) {
    // Создаем SQL-запрос для удаления всех строк с заданным serialNumAGV
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE_AGV_TO " WHERE serialNumberAGV = :serialNumberAGV");
    query.bindValue(":serialNumberAGV", serialNumAGV);

    // Выполняем запрос
    if (!query.exec()) {
        // Если произошла ошибка, выводим ее в отладочный лог
        qDebug() << "Error deleting records:";
        return false;
    }

    return true;
}


bool DataBase::dropTable(const QString &tableName) {
    QSqlQuery query;

    // Подготовка SQL-запроса для удаления таблицы
    QString sql = QString("DROP TABLE IF EXISTS %1").arg(tableName);
    query.prepare(sql);

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Error: Unable to drop table";
        return false;
    }

    return true;
}

bool DataBase::deleteModel(const QString &model) {
    // Создаем SQL-запрос для удаления всех строк с заданным serialNumAGV
    QSqlQuery query;
    query.prepare("DELETE FROM " TABLE_MODEL " WHERE model = :model");
    query.bindValue(":model", model);

    // Выполняем запрос
    if (!query.exec()) {
        // Если произошла ошибка, выводим ее в отладочный лог
        qDebug() << "Error deleting records:";
        return false;
    }

    return true;
}

bool DataBase::deleteTOFromSelectModelTable(const QString &nameTableModel, const QString &nameTo, const QString &frequencyTo) {
    // Создаем SQL-запрос
    QSqlQuery query;

    // Формируем запрос на удаление
    QString sql = QString("DELETE FROM %1 WHERE nameTo = :nameTo AND frequencyTo = :frequencyTo").arg(nameTableModel);

    query.prepare(sql);

    // Привязываем параметры к запросу
    query.bindValue(":nameTo", nameTo);
    query.bindValue(":frequencyTo", frequencyTo);

    // Выполняем запрос
    if (!query.exec()) {
        qDebug() << "Ошибка при удалении: ";
        return false;
    }
    return true;
}

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~update~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

bool DataBase::updateTOSelectTable(const QString& tableName, const QString& oldName, const QString& oldFrequency, const QString& newName, const QString& newFrequency) {

    // Формируем SQL-запрос
    QString sql = QString("UPDATE %1 SET nameTo = :newName, frequencyTo = :newFrequency WHERE nameTo = :oldName AND frequencyTo = :oldFrequency;").arg(tableName);

    QSqlQuery query;
    query.prepare(sql);

    // Привязываем параметры
    query.bindValue(":newName", newName);
    query.bindValue(":newFrequency", newFrequency);
    query.bindValue(":oldName", oldName);
    query.bindValue(":oldFrequency", oldFrequency);

    // Выполняем запрос
    if (!query.exec()) {
        return false;
        qDebug() << "Ошибка выполнения запроса:";
    }

    qDebug() << "Запись успешно обновлена.";
    return true;
}

bool DataBase::updateUser(const QString &oldLogin, const QString &newLogin, const QString &newName, const QString &newSurname, const QString &newPass) {

    QMutexLocker locker(&mutex);
    QSqlQuery query;

    // Подготовка SQL-запроса
    query.prepare("UPDATE " TABLE_USERS " SET login = :newLogin, name = :name, surname = :surname, pass = :pass WHERE login = :oldLogin");

    // Привязка параметров
    query.bindValue(":newLogin", newLogin);
    query.bindValue(":name", newName);
    query.bindValue(":surname", newSurname);
    query.bindValue(":pass", newPass);
    query.bindValue(":oldLogin", oldLogin);

    // Выполнение запроса
    if (!query.exec()) {
        qDebug() << "Error: Unable to update user";
        return false;
    }
    return true;
}

bool DataBase::updateAgv(const QString& oldName, const QString& oldSerialNumber,
                         const QString& newName, const QString& newSerialNumber,
                         const QString& versionFW, const QString& model,
                         const QString& ePlan) {
    // Подготовка SQL-запроса для обновления данных
    QString strUpdateAgv = QString("UPDATE %1 SET name = ?, serialNumber = ?, versionFW = ?, model = ?, ePlan = ? "
                                   "WHERE name = ? AND serialNumber = ?")
            .arg(TABLE_AGV);

    QSqlQuery query;
    query.prepare(strUpdateAgv);

    // Привязываем параметры к запросу
    query.addBindValue(newName);
    query.addBindValue(newSerialNumber);
    query.addBindValue(versionFW);
    query.addBindValue(model);
    query.addBindValue(ePlan);
    query.addBindValue(oldName);
    query.addBindValue(oldSerialNumber);

    // Выполнение запроса и проверка успешности выполнения
    if (!query.exec()) {
        qDebug() << "Ошибка обновления AGV:";
        return false;
    }

    return true;
}


bool DataBase::updateStatusToFromAgvToTable(const QString& serialNumberAGV, const QString& NameTo, const QString& newStatusTo) {

    // Создаем SQL-запрос для обновления статуса
    QSqlQuery query;
    query.prepare("UPDATE " TABLE_AGV_TO " SET statusTo = :newStatusTo WHERE serialNumberAGV = :serialNumberAGV AND nameTo = :nameTo");

    // Устанавливаем параметры запроса
    query.bindValue(":newStatusTo", newStatusTo);
    query.bindValue(":serialNumberAGV", serialNumberAGV);
    query.bindValue(":nameTo", NameTo);

    // Выполняем запрос
    if (!query.exec()) {
        qDebug() << "Ошибка выполнения запроса:"; //<< query.lastError().text();
        return false;
    }

    // Проверяем, были ли обновлены какие-либо строки
    if (query.numRowsAffected() > 0) {
        qDebug() << "Статус успешно обновлен.";
        return true;
    } else {
        qDebug() << "Запись не найдена или статус не изменен.";
        return false;
    }
}


//-----------------------------read IP---------------------------
QString DataBase::readIpFromFile() {
    QFile file("ip_config.txt"); // Путь к файлу
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return "localhost"; //в случае ошибки
    }

    QTextStream in(&file);
    QString ipAddress = in.readLine(); // Читаем первую строку файла

    file.close();
    return ipAddress; // Возвращаем считанный IP адрес
}
