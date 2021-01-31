//============================================================================
// Name        : value.cpp
// Author      : Piotr Wasilewski
// Version     : 1
// Copyright   : All rights reserved
// Description : Projekt licznika rowerowego
//============================================================================
#include "value.h"
#include <QObject>

value::value(QObject *parent) : QObject(parent)
{
    myValue = 0;
}
void value::setValue(int newValue)
{
    if(newValue != myValue)
    {
        myValue = newValue;
        emit valueChanged(myValue);
    }
}
