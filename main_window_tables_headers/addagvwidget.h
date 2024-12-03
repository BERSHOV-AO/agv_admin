#ifndef ADDAGVWIDGET_H
#define ADDAGVWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QDir>
#include <QComboBox>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>
#include "database.h"

#define ADD_AGV_STRING  "Добавление AGV в базу данных"

class AddAGVWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddAGVWidget(QWidget *parent = nullptr);
    QVBoxLayout *layout;
    QFormLayout *formLayout;

    QLineEdit *nameLineEdit;
    QLineEdit *serialNumberLineEdit;
    //    QLineEdit *fwVersionLineEdit;
    QLineEdit *modelLineEdit;
    //QLineEdit *documentationLineEdit;

    QPushButton *saveButton;

    QComboBox *documentationComboBox;
    QComboBox *fwVersionComboBox;

    qint64 getCurrentMillisecondsSinceEpoch();
    DataBase& db = DataBase::getInstance();

signals:

};

#endif // ADDAGVWIDGET_H
