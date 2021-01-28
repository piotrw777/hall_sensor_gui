//============================================================================
// Name        : value.h
// Author      : Piotr Wasilewski
// Version     : 1
// Copyright   : All rights reserved
// Description : Projekt licznika rowerowego
//============================================================================
#ifndef VALUE_H
#define VALUE_H

#include <QObject>
class MainWindow;
class value : public QObject
{
    Q_OBJECT
public:
    friend class MainWindow;
    explicit value(QObject *parent = nullptr);

signals:
    void valueChanged(int);

public slots:
    void setValue(int newValue);

private:
    int myValue;

};

#endif // VALUE_H
