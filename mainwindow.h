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

    QPushButton *addAGVButton;
    QPushButton *listAGVButton;
    QPushButton *logButton;

    QWidget* createAddAGVWidget();
    QWidget* createListAGVWidget();
    QWidget* createLogWidget();

    QLabel *titleLabel;
    QLabel *imageLabel;

    QFrame *line;

    QHBoxLayout* createButtonLayout();






};
#endif // MAINWINDOW_H
