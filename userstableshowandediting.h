#ifndef USERSTABLESHOWANDEDITING_H
#define USERSTABLESHOWANDEDITING_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include "database.h"
#include "usereditdialog.h"

class UsersTableShowAndEditing : public QWidget
{
    Q_OBJECT
public:
    explicit UsersTableShowAndEditing(QWidget *parent = nullptr);

    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    DataBase *db;

    void loadData();


private slots:
    void onCellDoubleClicked(int row, int column);

signals:

};

#endif // USERSTABLESHOWANDEDITING_H
