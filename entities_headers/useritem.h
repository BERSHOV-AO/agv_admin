#ifndef USERITEM_H
#define USERITEM_H

#include <QString>


class UserItem
{
public:
    UserItem(const QString &name, const QString &surname, const QString &login,
             const QString &pass);

    QString getName() const;
    QString getSurname() const;
    QString getLogin() const;
    QString getPass() const;

private:
    QString name;
    QString surname;
    QString login;
    QString pass;
};

#endif // USERITEM_H
