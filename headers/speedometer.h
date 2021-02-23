#ifndef SPEEDOMETER_H
#define SPEEDOMETER_H

#include <QWidget>

class speedometer : public QWidget
{
    Q_OBJECT
public:
    explicit speedometer(QWidget *parent = nullptr);
    ~speedometer(){}

protected:
    void paintEvent(QPaintEvent *event);
signals:

public slots:
    void changeValue(double);

private:
    double val;

};

#endif // SPEEDOMETER_H
