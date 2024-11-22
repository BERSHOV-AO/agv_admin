#ifndef TABLEAGVSHOW_H
#define TABLEAGVSHOW_H

#include <QWidget>
#include <QTableWidget>
#include <QVBoxLayout>
#include <QHeaderView>
#include <QDateTime>
#include <QHBoxLayout>
#include <QPushButton>
#include <QComboBox>
#include "database.h"
#include "agvadddialog.h"
#include "agveditdialog.h"
#include "entities_headers/agvitem.h"
#include "tabletooneagvshowdialog.h"
#include "modelredactordialog.h"

class TableAgvShow : public QWidget
{
    Q_OBJECT
public:
    explicit TableAgvShow(QWidget *parent = nullptr);
    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    QPushButton *addAGVButton;
    QPushButton *modeEditAGV;
    DataBase *db;

    void loadData();
    QString formatDateFromMilliseconds(const QString& millisecondsStr);

private slots:
    void onCellDoubleClicked(int row, int column);
    void onAddAGVClicked();
signals:

};

#endif // TABLEAGVSHOW_H
