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
#include "agv_headers/tableagvshow.h"
#include "main_window_tables_headers/addagvwidget.h"
#include "main_window_tables_headers/tablelogagvshow.h"
#include "main_window_tables_headers/userstableshowandediting.h"
#include "main_window_tables_headers/modelredactordialog.h"
#include "user_headers/usereditdialog.h"
#include <QSqlDatabase>
#include <QStringList>
#include <QDebug>
#include <settingdialog.h>

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
    QPushButton *settingsButton;

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

private slots:
    void oneSettingClicked();
};
#endif // MAINWINDOW_H
