#ifndef USEREDITDIALOG_H
#define USEREDITDIALOG_H


#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include "useritem.h"

class UserEditDialog : public QDialog
{
    Q_OBJECT
public:
    explicit UserEditDialog(const UserItem &user, QWidget *parent = nullptr);
    UserItem getUser() const;

private slots:
    void saveData();

private:
    UserItem user;
    QLineEdit *nameEdit;
    QLineEdit *surnameEdit;
    QLineEdit *loginEdit;
    QLineEdit *passEdit;
};

#endif // USEREDITDIALOG_H
