#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(500, 400);

    list = new QListWidget(this);

    btn = new QPushButton("Button", this);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(addInfo()));

    grid = new QGridLayout(this);
    grid->addWidget(list, 0, 0);
    grid->addWidget(btn, 1, 0);
}

void MainWindow::addInfo()
{
    int i = 0, num = 0;
    char** wire = new char*[30];
    while(i < 30)
        wire[i++] = new char[256];

    num = Wifi::getWifiList(wire);

    i = 0;
    list->clear();
    while(i < num){
        list->addItem(wire[i]);
        delete(wire[i++]);
    }
    delete(wire);
}
