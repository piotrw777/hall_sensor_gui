#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QWidget>
#include <QVector>
#include <QString>

class speedometer : public QWidget
{
    Q_OBJECT
public:
    explicit speedometer(QWidget *parent = nullptr);
    ~speedometer(){}

    int getAngle() const;
    void setAngle(int value);

    int getMax_speed() const;
    void setMax_speed(int value);

    int getStep() const;
    void setStep(int value);

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void changeValue(double);
    void change_unitNr(int);

private:
    double val;
    int unitNr;
    int angle;
    int max_speed;
    int step;
    int regions;
    double unitSpeedAngle;
    double ticksAngle;

    QVector<QString> speed_suffixes;
};

#endif // SPEEDOMETER_H
