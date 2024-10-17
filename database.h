#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QList>
#include <QStringList>
#include "agvitem.h"
#include "useritem.h"
#include "logitem.h"
#include "modelagvitem.h"
#include "toitem.h"
#include "agvtoitem.h"

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_NAME            "agv_db.db"
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

class DataBase : public QObject
{
    Q_OBJECT
public:
    void connectToDataBase();
    /* Внутренние методы для работы с базой данных */
    bool openDataBase();                                                                  // Открытие базы данных
    bool restoreDataBase();                                                               // Востановление базы данных
    bool createTable();                                                                   // Создание базы таблицы в базе данных
    bool closeDataBase();

    //~~~~~~~~create~~~~~~~~~~
    bool createNewModelTable(const QString tableName);
    //~~~~~~~~~save~~~~~~~~~~~
    bool saveAgvItem(QString name, QString serialNumber, QString versionFW, QString model, QString ePlan, QString dataLastTo);
    bool saveLogItem(QString typeLog, QString tabelNum, QString timeOpenApp, QString serialNumberAgv, QString nameTO, QString timeToAgv);
    bool saveAgvTOItem(QString nameTo, QString serialNumberAGV, QString frequencyOfTo, QString statusTo, QString dataTo);
    bool saveUserItem(QString name, QString surname, QString login, QString pass);
    bool saveModelItem(QString model);
    bool saveTOForSelectModel(const QString nameTableModel, const QString nameTo, const QString frequencyTo);
    //~~~~~~~~~update~~~~~~~~~~~
    bool updateUser(const QString &login, const QString &newName, const QString &newSurname, const QString &newPass);
    //~~~~~~~~~delete~~~~~~~~~~~
    bool dropTable(const QString &tableName);
    bool deleteUser(const QString &login, const QString &name, const QString &surname);
    bool deleteAgv(const QString &serialNumber);
    bool deleteAllToOneAgv(const QString serialNumAGV);
    bool deleteModel(const QString &model);

    //~~~~~~~~~fetch~~~~~~~~~~~
    QList<AgvItem> fetchAGVs();
    QList<UserItem> fetchUsers();
    QList<LogItem> fetchLogs();
    QList<ModelAgvItem> fetchModels();
    QList<AGVTOItem> fetchToOneAgv(const QString serialNumAGV);
    QList<TOItem> fetchTO(const QString nameTableTO);

    explicit DataBase(QObject *parent = nullptr);

private:
    QSqlDatabase db;

signals:

};

#endif // DATABASE_H
