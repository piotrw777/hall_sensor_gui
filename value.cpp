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
        emit valueChanged(newValue);
    }
}
