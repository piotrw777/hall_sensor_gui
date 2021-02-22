#include "speedometer.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QString>
#include <cmath>
#include <QFont>
#include <QVector>

speedometer::speedometer(QWidget *parent) : QWidget(parent)
{
    val = 0;
}
double cosd(double r) {
    return cos(3.141592653589*r/180);
}
double sind(double r) {
    return sin(3.141592653589*r/180);
}

void speedometer::paintEvent(QPaintEvent *event)
{

    //static const double pi = 3.1415926535;
    const int W = 200;
    const int T = 160;
    const int Re = 10;
    const int R = 8;
    const int CP = 180;
    const int ANGLE = 270;
    const int regions = 20;

    int side = qMin(width(), height());
    QPainter painter(this);
    painter.setViewport( (width()-side)/2, (height()-side)/2, side, side);
    painter.setWindow(-W,-W, 2*W, 2*W);
    painter.setRenderHint(QPainter::Antialiasing);

    QPoint A(-T, -T);
    QPoint B(T, T);
    QRect P(A, B);

    QRadialGradient grad1(QPoint(0,0), 180);
    grad1.setColorAt(0.0, QColor(255, 255, 255, 100));
    grad1.setColorAt(0.2, QColor(0,0,250, 100));
    grad1.setColorAt(0.8, QColor(0,0,0,100));

    QPen piePen(Qt::NoPen);
    QBrush pieBrush(grad1);

    painter.setPen(piePen);
    painter.setBrush(pieBrush);
    painter.drawPie(P,-16*(ANGLE/2.0-90), ANGLE*16);

    //draw central circle
    QPoint A1(-Re, -Re);
    QPoint B1(Re, Re);
    QRect P1(A1, B1);

    QPen ellipsePen(Qt::green);
    ellipsePen.setWidth(1);
    QBrush ellipseBrush(Qt::green);

    painter.setPen(Qt::NoPen);
    painter.setBrush(ellipseBrush);
    painter.drawEllipse(P1);

    //drawing line 0km/h
//pomoicniczy prostokat

//    const int d = 15;
//    QPoint CBase(-CP/sqrt(2), CP/sqrt(2));

//    QPoint Acp(-CP/sqrt(2)-d, CP/sqrt(2)-d);
//    QPoint Bcp(-CP/sqrt(2)+d, CP/sqrt(2)+d);
//    QRectF pomRec(Acp,Bcp);
//    QPainter pomRecPainter(this);
//    pomRecPainter.setWindow(-W,-W, 2*W, 2*W);

//    QPen pomRecPen(Qt::black);
//    pomRecPen.setWidth(5);
//    pomRecPainter.setPen(pomRecPen);
//    pomRecPainter.drawRect(pomRec);
//    pomRecPainter.rotate(27);
//    pomRecPainter.drawRect(pomRec);

    QPoint L1(-T/sqrt(2), T/sqrt(2));
    QPoint L2(-T/1.7,T/1.7);
    QPoint L3(-T/1.5,T/1.5);

    QPen linePen(Qt::yellow);
    linePen.setWidth(2);
    painter.setPen(linePen);
    painter.drawLine(L1, L2);


    painter.save();
    for(int k = 0; k < regions; k++) {
        painter.rotate(1.0*ANGLE/regions);
        if(k % 2 == 0) {
            painter.drawLine(L1, L3);
        }
        else
            painter.drawLine(L1, L2);
    }
    painter.restore();

    //draw arrow
    QPointF R1(-R/sqrt(2),-R/sqrt(2));
    QPointF R2(R/sqrt(2), R/sqrt(2));
    QPointF R3(-T/sqrt(2), T/sqrt(2));

    QPointF ArrowPoints[3]={R1, R2, R3};
    QPen arrowPen(Qt::NoPen);
    QLinearGradient arrowgrad(QPoint(0,0), R3);
    arrowgrad.setColorAt(0, Qt::green);
    arrowgrad.setColorAt(0.6, Qt::white);
    arrowgrad.setColorAt(0.9,Qt::yellow);
    QBrush arrowBrush(Qt::green);

    painter.setBrush(arrowBrush);
    painter.setPen(arrowPen);

    painter.save();
    painter.rotate(val*2.7);
    painter.drawConvexPolygon(ArrowPoints, 3);
    painter.restore();


    //koło pomocnicze
//    QPainter pomCircle(this);
//    QRect CPRect(-CP, -CP, 2*CP, 2*CP);

//    QPen pomCirclePen(Qt::red);
//    pomCirclePen.setWidth(2);

//    pomCircle.setWindow(-W,-W, 2*W, 2*W);
//    pomCircle.setRenderHint(QPainter::Antialiasing);
//    pomCircle.setPen(pomCirclePen);
//    pomCircle.drawEllipse(CPRect);


    //punkty pomocnicze

    QVector<QPoint> centralPoints;

    for(int k = 0; k < 21; k++) {
        centralPoints.push_back(QPoint(CP*cosd(225-k*13.5), -CP*sind(225-k*13.5)));
    }


//    QPainter pointsPainter(this);
//    pointsPainter.setWindow(-W,-W, 2*W, 2*W);
//    pointsPainter.setRenderHint(QPainter::Antialiasing);
//    QPen pointsPen(Qt::yellow);
//    pointsPen.setWidth(2);
//    pointsPainter.setPen(pointsPen);

//    for(int k = 0; k < 21; k++) {
//        pointsPainter.drawPoint(centralPoints[k]);
//    }


    QPainter textpainter(this);
    textpainter.setViewport( (width()-side)/2, (height()-side)/2, side, side);
    textpainter.setWindow(-W,-W, 2*W, 2*W);

    QFont myFont;
    myFont.setFamily("Tahoma");
    myFont.setPointSize(14);

    QFont myFont2;
    myFont2.setFamily("Arial");
    myFont2.setPointSize(10);
    textpainter.setFont(myFont);

    int v = 0;
    for(int k = 0; k < 21; k++) {
        if(k%2 == 0) {
            textpainter.setFont(myFont);
        }
        else {
            textpainter.setFont(myFont2);
        }
        if(k% 2 == 0) textpainter.drawText(QRectF(centralPoints[k]-QPoint(20,20),centralPoints[k]+QPoint(20,20)),Qt::AlignCenter, QString::number(v));
        v += 5;
    }

    QPen arcPen(Qt::red);
    arcPen.setWidth(5);
    arcPen.setCapStyle(Qt::FlatCap);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(arcPen);
    painter.drawArc(P,225*16-16*2.7*val,16*2.7*val);

}

void speedometer::changeValue(double newval)
{
    val = newval;
    update();
}
