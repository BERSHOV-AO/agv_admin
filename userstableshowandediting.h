#ifndef USERSTABLESHOWANDEDITING_H
#define USERSTABLESHOWANDEDITING_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>

class UsersTableShowAndEditing : public QWidget
{
    Q_OBJECT
public:
    explicit UsersTableShowAndEditing(QWidget *parent = nullptr);

    QVBoxLayout *layout;
    QTableWidget *tableWidget;

    void loadData();

signals:

};

#endif // USERSTABLESHOWANDEDITING_H
