#ifndef USERADDDIALOG_H
#define USERADDDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QMessageBox>
#include <QLabel>
#include "useritem.h"
#include "database.h"

class UserAddDialog : public QDialog
{
    Q_OBJECT
public:
    UserAddDialog(QWidget *parent = nullptr);

private slots:
    void addUser();

private:
   // UserItem user;
    QPushButton *saveButton;
    QLineEdit *nameEdit;
    QLineEdit *surnameEdit;
    QLineEdit *loginEdit;
    QLineEdit *passEdit;
    QPushButton* deleteButton;
    DataBase *db;
};

#endif // USERADDDIALOG_H
