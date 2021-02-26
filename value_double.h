#ifndef VALUE_DOUBLE_H
#define VALUE_DOUBLE_H

#include <QObject>
#include <QString>

class value_double : public QObject
{
    Q_OBJECT
public:
    explicit value_double(QObject *parent = nullptr);
    double getValue() const;
public slots:
    void changeValue(double newval);
    void increaseValue(double val);
    void resetValue();
    void change_unit(int);

signals:
    //void valueChanged(double);
    void valueChanged(QString);

private:
    double myvalue;
    int unit_nr;
    double distance_coefficients[3];
    double distance_inverse_coefficients[3];
};

#endif // VALUE_DOUBLE_H
