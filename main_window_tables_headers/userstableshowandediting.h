#ifndef USERSTABLESHOWANDEDITING_H
#define USERSTABLESHOWANDEDITING_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QHBoxLayout>
#include "database.h"
#include "user_headers/usereditdialog.h"
#include "user_headers/useradddialog.h"

class UsersTableShowAndEditing : public QWidget
{
    Q_OBJECT
public:
    explicit UsersTableShowAndEditing(QWidget *parent = nullptr);

    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    QPushButton *addUserButton;
    DataBase *db;

    void loadData();
    void updateTable();

private slots:
    void onCellDoubleClicked(int row);
    void onAddUserClicked();

};

#endif // USERSTABLESHOWANDEDITING_H
