//============================================================================
// Name        : main.cpp
// Author      : Piotr Wasilewski
// Version     : 1
// Copyright   : All rights reserved
// Description : Projekt licznika rowerowego
//===========================================================================
#include "mainwindow.h"
#include <QApplication>
#include "hall_sensor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    return a.exec();
}
