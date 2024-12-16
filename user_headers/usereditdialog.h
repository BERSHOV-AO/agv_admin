#ifndef USEREDITDIALOG_H
#define USEREDITDIALOG_H

#include <QThread>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include "entities_headers/useritem.h"
#include "database.h"
#include "databaseworker.h"

class UserEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserEditDialog(const UserItem &user, QWidget *parent = nullptr);
    UserItem getUser() const;

private slots:
    void saveData();
    void deleteUser();

signals:
    void userDeleted();

private:
    UserItem user;
    QLineEdit *nameEdit;
    QLineEdit *surnameEdit;
    QLineEdit *loginEdit;
    QLineEdit *passEdit;
    QPushButton* deleteButton;
    DataBase& db = DataBase::getInstance();
};

#endif // USEREDITDIALOG_H
