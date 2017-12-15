#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QtWidgets>
#include "stdafx.h"
#include "wifi.h"
#include <QtConcurrent/QtConcurrent>

class MainWindow : public QWidget
{
    Q_OBJECT
    QListWidget* list;
    QPushButton* btn;
    QGridLayout* grid;
    static void timer(MainWindow* parent);
public:
    explicit MainWindow(QWidget *parent = 0);

signals:

public slots:
    void addInfo();
    void connectWifi();
};

#endif // MAINWINDOW_H
