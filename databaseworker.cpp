#include "databaseworker.h"

DatabaseWorker::DatabaseWorker(QObject *parent) : QObject(parent)
{}
void DatabaseWorker::updateUser(const QString &oldLogin, const QString &newLogin,
                                 const QString &newName, const QString &newSurname, const QString &newPass) {

    bool success = db.updateUser(oldLogin, newLogin, newName, newSurname, newPass);
    emit updateUserFinished(success);
}

void DatabaseWorker::deleteUser(const QString &login, const QString &name, const QString &surname) {

    bool success = db.deleteUser(login, name, surname);
    emit deleteUserFinished(success);
}
