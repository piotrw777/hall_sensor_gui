#include "value_double.h"

value_double::value_double(QObject *parent) : QObject(parent), myvalue(0)
{
    distance_coefficients[0] = 0.001;
    distance_coefficients[1] = 1;
    distance_coefficients[2] = 0.0006213727366;

    distance_inverse_coefficients[0] = 1000;
    distance_inverse_coefficients[1] = 1;
    distance_inverse_coefficients[2] = 1609.34;
}

double value_double::getValue() const
{
    return myvalue;
}

void value_double::changeValue(double newval)
{
    if(newval != myvalue)
    {
        myvalue = newval;
        //emit valueChanged(newval);
        QString value_str = QString::number(myvalue, 'f',0);
        emit valueChanged(value_str);
    }
}

void value_double::increaseValue(double add)
{
    myvalue += add;
   // emit valueChanged(myvalue);
    QString value_str = QString::number(myvalue, 'f',0);
    emit valueChanged(value_str);
}

void value_double::resetValue()
{
    myvalue = 0;
    //emit valueChanged(0);
    emit valueChanged("0");
}

void value_double::change_unit(int new_unit)
{
    if(new_unit != unit_nr)
    {
        myvalue *= distance_inverse_coefficients[unit_nr]*distance_coefficients[new_unit];
        unit_nr = new_unit;
        //emit valueChanged(myvalue);
        QString value_str = QString::number(myvalue, 'f',0);
        emit valueChanged(value_str);
    }
}
