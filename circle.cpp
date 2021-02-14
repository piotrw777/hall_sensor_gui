#include "circle.h"

#include <QPainter>
#include <QWidget>
#include <math.h>

circle::circle(QWidget *parent) : QWidget(parent)
{
    val = 100;
}

void circle::paintEvent(QPaintEvent *event)
{
    static const double pi = 3.141592;
    QPainter painter(this);
    painter.setWindow(-100, -100, 200, 200);
    QPoint A(-80, -80);
    QPoint B(80, 80);
    QPoint O(0,0);
    QRect P(A, B);
    painter.drawEllipse(P);

    QPoint X(80*cos(val*pi/100),-80*sin(val*pi/100));
    painter.setPen(QPen(Qt::black,12));
    painter.drawPoint(X);
}

void circle::changeValue(double newval)
{
    val = newval;
    update();
}
