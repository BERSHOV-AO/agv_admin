#ifndef TABLESELECTEDMODELSHOWDIALOG_H
#define TABLESELECTEDMODELSHOWDIALOG_H

#include <QDialog>
#include <QTableWidget>
#include <QHeaderView>
#include <QPushButton>
#include <QDateTime>
#include <QMessageBox>
#include "database.h"
#include <QBrush>
#include <QVBoxLayout>
#include "entities_headers/toitem.h"
#include "toaddfrommodeldialog.h"
#include "toeditdialog.h"

class TableSelectedModelShowDialog : public QDialog
{
    Q_OBJECT
public:
    TableSelectedModelShowDialog(const QString &nameTableModel, QWidget *parent = nullptr);

private:
    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    DataBase& db = DataBase::getInstance();

    QPushButton *deleteButton;
    QPushButton *addModelButton;
    QString nameTableModel;

    void loadData();

private slots:
    void oneAddModelClicked();
    void oneDeleteAGVClicked();
    void onCellDoubleClicked(int row);
};

#endif // TABLESELECTEDMODELSHOWDIALOG_H
