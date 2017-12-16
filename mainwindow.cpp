#include "mainwindow.h"

void MainWindow::timer(MainWindow *parent)
{
    while(true){
        emit(parent->addInfo());
        sleep(5);
    }
}

MainWindow::MainWindow(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(600, 350);

    list = new QListWidget(this);

    btn = new QPushButton("Connect", this);
    connect(btn, SIGNAL(clicked(bool)), this, SLOT(connectWifi()));

    grid = new QGridLayout(this);
    grid->addWidget(list, 0, 0);
    grid->addWidget(btn, 1, 0);

    QtConcurrent::run(timer, this);
}

void MainWindow::addInfo()
{
    int i = 0, num = 0;
    char** wire = new char*[30];
    while(i < 30){
        wire[i] = new char[256];
        wire[i][0] = '\0';
        i++;
    }

    num = Wifi::getWifiList(wire);
    i = 0;
    if(num && list->count() != num)
    {
        if(list->count())
            list->clear();
        while(i < num)
            list->addItem(wire[i++]);
    }
    i = 0;
    while(i < 30)
        delete(wire[i++]);
    delete(wire);
}

void MainWindow::connectWifi()
{
    if(list->currentItem() != NULL){
        Wifi::connect(list->currentItem()->text().toStdString().c_str());
    }
}
