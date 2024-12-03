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
#include "agv_headers/agvadddialog.h"
#include "agv_headers/agveditdialog.h"
#include "entities_headers/agvitem.h"
#include "tabletooneagvshowdialog.h"
#include "main_window_tables_headers/modelredactordialog.h"
#include <QFuture>
#include <QtConcurrent>

class TableAgvShow : public QWidget
{
    Q_OBJECT
public:
    explicit TableAgvShow(QWidget *parent = nullptr);
    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    QPushButton *addAGVButton;
    QPushButton *modeEditAGV;
    DataBase& db = DataBase::getInstance();

    void loadData();
    QString formatDateFromMilliseconds(const QString& millisecondsStr);

private slots:
    void onCellDoubleClicked(int row);
    void onAddAGVClicked();
signals:

};

#endif // TABLEAGVSHOW_H
