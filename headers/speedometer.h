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

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void changeValue(double);
    void change_unitNr(int);

private:
    double val;
    int unitNr;
    QVector<QString> speed_suffixes;
};

#endif // SPEEDOMETER_H
