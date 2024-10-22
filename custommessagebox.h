#ifndef CUSTOMMESSAGEBOX_H
#define CUSTOMMESSAGEBOX_H


#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPalette>

class CustomMessageBox : public QDialog {
    Q_OBJECT

public:
    explicit CustomMessageBox(const QString &message, QWidget *parent = nullptr);

private:
    QVBoxLayout *layout;
    QLabel *label;
    QPushButton *yesButton;
    QPushButton *noButton;
};

#endif // CUSTOMMESSAGEBOX_H
