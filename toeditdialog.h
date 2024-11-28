#ifndef TOEDITDIALOG_H
#define TOEDITDIALOG_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include "database.h"
#include "entities_headers/toitem.h"
#include "custommessagebox.h"


class TOEditDialog : public QDialog
{
    Q_OBJECT
public:
    TOEditDialog(const TOItem &toItem, const QString &nameTableModel, QWidget *parent = nullptr);
    TOItem getTo() const;

private slots:
    void saveDataTo();
    void deleteTo();

private:
    TOItem toItem;
    QString nameTableModel;
    QLineEdit* nameToEdit;
    QLineEdit* frequencyToEdit;
    QPushButton* deleteButton;
    QPushButton* saveButton;
    DataBase *db;
};

#endif // TOEDITDIALOG_H
