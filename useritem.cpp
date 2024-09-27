#include "useritem.h"

UserItem::UserItem(const QString &name,
                   const QString &surname,
                   const QString &login,
                   const QString &pass)
    : name(name),
      surname(surname),
      login(login),
      pass(pass) {}

QString UserItem::getName() const { return name; }
QString UserItem::getSurname() const { return surname; }
QString UserItem::getLogin() const { return login; }
QString UserItem::getPass() const { return pass; }

