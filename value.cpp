#include "value.h"

value::value(QObject *parent) : QObject(parent), myvalue(0)
{

}

void value::changeValue(int newval)
{
    if(newval != myvalue)
    {
        myvalue = newval;
        emit valueChanged(newval);
    }
}

void value::increaseValue()
{
    myvalue++;
    emit valueChanged(myvalue);
}
