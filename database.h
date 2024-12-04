#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QStringList>
#include <QMutex>
#include <QMutexLocker>
#include "entities_headers/agvitem.h"
#include "entities_headers/useritem.h"
#include "entities_headers/logitem.h"
#include "entities_headers/modelagvitem.h"
#include "entities_headers/toitem.h"
#include "entities_headers/agvtoitem.h"

/* Директивы имен таблицы, полей таблицы и базы данных */
//#define DATABASE_NAME            "agv_db_new.db"
#define DIR_AND_NAME_DATABASE    "./agv_db.db"
//#define DATABASE_HOSTNAME       "NameDataBase"                                              // имя хоста
//#define DIR_AND_NAME_DATABASE   "./dirDB/dbLogbook.db"                                      // Dir таблицы и имя
#define TABLE_AGV                "agv"
#define TABLE_AGV_TO             "agv_to"
#define TABLE_LOG                "log"
#define TABLE_USERS              "users"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define TABLE_MODEL              "model"
#define TABLE_AGV_1100_ST        "AGV_1100_ST"
#define TABLE_AGV_3000_ST        "AGV_1100_2P"
#define TABLE_AGV_1100_2P        "AGV_1100_2T"
#define TABLE_AGV_1100_2T        "AGV_3000_ST"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
#define HOST_NAME       "localhost"
#define DATABASE_NAME   "agv_db"   //test_db
//#define DATABASE_NAME   "test_db"
#define USER_NAME       "root"
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class DataBase : public QObject
{
    Q_OBJECT
public:

    static DataBase& getInstance();
    //~~~~~~~new~~~~~~~
    bool createTable();
    bool hasTables();
    //~~~~~~~~~~~~~~~~~~~~~
    bool connectToDataBase();

    bool connectToDataBaseinFerst();

    /* Внутренние методы для работы с базой данных */
    bool openDataBase();                                                                  // Открытие базы данных
    bool restoreDataBase();                                                               // Востановление базы данных
    //bool createTable();                                                                   // Создание базы таблицы в базе данных
    bool closeDataBase();

    //~~~~~~~~~create~~~~~~~~~~~~
    bool createNewModelTable(const QString tableName);
    //~~~~~~~~~~save~~~~~~~~~~~~~
    bool saveAgvItem(QString name, QString serialNumber, QString versionFW, QString model, QString ePlan, QString dataLastTo);
    bool saveLogItem(QString typeLog, QString tabelNum, QString timeOpenApp, QString serialNumberAgv, QString nameTO, QString timeToAgv);
    bool saveAgvTOItem(QString nameTo, QString serialNumberAGV, QString frequencyOfTo, QString statusTo, QString dataTo);
    bool saveUserItem(QString name, QString surname, QString login, QString pass);
    bool saveModelItem(QString model);
    bool saveTOForSelectModel(const QString nameTableModel, const QString nameTo, const QString frequencyTo);
    //~~~~~~~~~~update~~~~~~~~~~~
    bool updateUser(const QString &oldLogin, const QString &newLogin, const QString &newName, const QString &newSurname, const QString &newPass);
    bool updateTOSelectTable(const QString& tableName, const QString& oldName, const QString& oldFrequency, const QString& newName, const QString& newFrequency);
    bool updateAgv(const QString& oldName, const QString& oldSerialNumber,
                   const QString& newName, const QString& newSerialNumber,
                   const QString& versionFW, const QString& model,
                   const QString& ePlan);
    bool updateStatusToFromAgvToTable(const QString& serialNumberAGV, const QString& NameTo, const QString& newStatusTo);

    //~~~~~~~~~~delete~~~~~~~~~~~
    bool dropTable(const QString &tableName);
    bool deleteUser(const QString &login, const QString &name, const QString &surname);
    bool deleteAgv(const QString &serialNumber);
    bool deleteAllToOneAgv(const QString serialNumAGV);
    bool deleteModel(const QString &model);
    bool deleteTOFromSelectModelTable(const QString &nameTableModel, const QString &nameTo, const QString &frequencyTo);
    //~~~~~~~~fetch -> get~~~~~~~~
    QList<AGVTOItem> getAllAgvTO();
    QList<AgvItem> fetchAGVs();
    QList<UserItem> fetchUsers();
    QList<LogItem> fetchLogs();
    QList<ModelAgvItem> fetchModels();
    QList<AGVTOItem> fetchToOneAgv(const QString serialNumAGV);
    QList<TOItem> fetchTO(const QString nameTableTO);

    QMutex mutex; // Мьютекс для защиты доступа

    explicit DataBase(QObject *parent = nullptr);

private:
    QSqlDatabase db;
    //DataBase() {} // Конструктор приватный
    ~DataBase() {}
    DataBase(const DataBase&) = delete; // Запрет копирования
    DataBase& operator=(const DataBase&) = delete; // Запрет присваивани

signals:
    //------user signals-------
    void saveUserFinished();
    void updateUserFinished();
    void deleteUserFinished();

};

#endif // DATABASE_H
