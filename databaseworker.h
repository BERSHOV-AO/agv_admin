#ifndef DATABASEWORKER_H
#define DATABASEWORKER_H

#include <QObject>
#include "database.h"
#include <QString>

class DatabaseWorker : public QObject
{
    Q_OBJECT
public:
    explicit DatabaseWorker(QObject *parent = nullptr);
    DataBase& db = DataBase::getInstance();

public slots:
    void updateUser(const QString &oldLogin, const QString &newLogin,
                    const QString &newName, const QString &newSurname, const QString &newPass);

    void deleteUser(const QString &login, const QString &name, const QString &surname);

signals:
    void updateUserFinished(bool success);
    void deleteUserFinished(bool success);

};

#endif // DATABASEWORKER_H
