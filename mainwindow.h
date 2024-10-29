#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QApplication>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>
#include <QLabel>
#include <QPixmap>
#include <QHBoxLayout>
#include <QFrame>
#include "tableagvshow.h"
#include "addagvwidget.h"
#include "tablelogagvshow.h"
#include "userstableshowandediting.h"
#include "usereditdialog.h"
class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    QStackedWidget *stackedWidget;

    QWidget *addAGVWidget;
    QWidget *listAGVWidget;
    QWidget *logWidget;
    QWidget *usersWidget;
    QWidget *modelWidget;

    QPushButton *usersButton;
    QPushButton *addAGVButton;
    QPushButton *listAGVButton;
    QPushButton *logButton;
    QPushButton *modelButton;

    QWidget* createAddAGVWidget();
    QWidget* createListAGVWidget();
    QWidget* createLogWidget();
    QWidget* createUsresWidget();
    QWidget* createModelWidget();

    void clearStackedWidget();

    void updateUsersData();
    void updateAddAGVData();
    void updateListAGVData();
    void updateLogData();
    void updateModelData();
    void replaceWidgetAt(int index, QWidget* newWidget);

    QLabel *titleLabel;
    QLabel *imageLabel;
    QFrame *line;

    QHBoxLayout* createButtonLayout();
};
#endif // MAINWINDOW_H
