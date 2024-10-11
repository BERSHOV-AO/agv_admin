#ifndef MODELREDACTORDIALOG_H
#define MODELREDACTORDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QDebug>
#include <QMessageBox>
#include <QComboBox>
#include <QLabel>
#include <QDir>
#include <QDateTime>
#include <QTableWidget>
#include <QHeaderView>
#include "database.h"
#include "modelagvitem.h"
#include "modeladddialog.h"

class ModelRedactorWidget : public QWidget
{
public:
    ModelRedactorWidget(QWidget *parent = nullptr);

private:

    QVBoxLayout *layout;
    QTableWidget *tableWidget;
    QPushButton *addModelButton;
    DataBase *db;

    void loadData();

private slots:
    void onAddModelClicked();
    void onCellDoubleClicked(int row, int column);

};

#endif // MODELREDACTORDIALOG_H
