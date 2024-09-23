#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QFile>
#include <QDebug>
#include <QList>
#include "agvitem.h"

/* Директивы имен таблицы, полей таблицы и базы данных */
#define DATABASE_NAME           "agv_db.db"
#define DIR_AND_NAME_DATABASE   "./agv_db.db"
//#define DATABASE_HOSTNAME       "NameDataBase"                                              // имя хоста
//#define DIR_AND_NAME_DATABASE   "./dirDB/dbLogbook.db"                                      // Dir таблицы и имя
#define TABLE_AGV                "agv"
#define TABLE_AGV_TO             "agv_to"
#define TABLE_LOG                "log"
#define TABLE_MODEL              "model"
#define TABLE_USERS              "users"

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
    bool saveAgvItem(QString name, QString serialNumber, QString versionFW, QString model, QString ePlan, QString dataLastTo);
    QList<AgvItem> fetchAGVs();

    explicit DataBase(QObject *parent = nullptr);

private:
    QSqlDatabase db;

signals:

};

#endif // DATABASE_H
