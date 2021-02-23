#ifndef UNITCHANGER_H
#define UNITCHANGER_H

#include <QObject>
#include <QVector>
#include <QString>

class unitChanger : public QObject
{
    Q_OBJECT
public:
    explicit unitChanger(QObject *parent = nullptr);

signals:
    void speed_change(QString);
    void distance_change(QString);
    void average_speed_change(QString);
    void time_trip_change(QString);

public slots:
    //void speed_change(double);
    //void distance_change(double);
    //void average_speed_change(double);
    void time_trip_change(double);

private:
    int unitNumber;
    double time_trip;
    //double speed;
    //double rpm;
    //double average_speed;
    QVector<QString> speed_suffixes;
    QVector<QString> distance_suffixes;
    QVector<double> speed_coefficients;
    QVector<double> distance_coefficients;
};

#endif // UNITCHANGER_H
