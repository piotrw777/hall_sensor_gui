#include "speedometer.h"
#include <QPainter>
#include <QPen>
#include <QBrush>
#include <QString>
#include <cmath>
#include <QFont>
#include <QVector>

#define drawPomRects 0

speedometer::speedometer(QWidget *parent) : QWidget(parent)
{
    unitNr = 0;
    val = 0;
    speed_suffixes = {"km/h", "m/s", "mph"};
    angle = 270;
    max_speed = 100;
    step = 10;
}
double cosd(double r) {
    return cos(3.141592653589*r/180);
}
double sind(double r) {
    return sin(3.141592653589*r/180);
}
QRectF createQRectF(QPointF center, qreal width, qreal height) {
    QPointF pom(width/2, height/2);
    return QRectF(center-pom, center+pom);
}
void speedometer::paintEvent(QPaintEvent *event)
{
    const int W = 200;
    const int T = 160;
    const int Re = 10;
    const int R = 8;
    const int CP = 185;
    double stretch_angle = 90+angle/2.0;
    regions = 2*max_speed/step;
    unitSpeedAngle = static_cast<double>(angle)/max_speed;
    ticksAngle = static_cast<double>(angle)/regions;

    int side = qMin(width(), height());
    QPainter painter(this);
    painter.setViewport( (width()-side)/2, (height()-side)/2, side, side);
    painter.setWindow(-W,-W, 2*W, 2*W);
    painter.setRenderHint(QPainter::Antialiasing);
    //painter.translate(0,50);

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
    painter.drawPie(P,-16*(angle/2.0-90), angle*16);

#if(drawPomRects == 1)
    painter.drawRect(createQRectF(QPointF(0,0), side, side));
#endif
    //draw central circle
    QPoint A1(-Re, -Re);
    QPoint B1(Re, Re);
    QRect P1(A1, B1);

    QPen ellipsePen(Qt::green);
    ellipsePen.setWidth(1);

//    QRadialGradient grad3(QPointF(0,0),10);
//    grad3.setColorAt(0,QColor(100, 250, 180));
//    grad3.setColorAt(0.4,QColor(80, 180, 20));
//    grad3.setColorAt(0.9,QColor(200, 230, 240));

    QBrush ellipseBrush(Qt::green);
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

//    QPoint L1(-T/sqrt(2), T/sqrt(2));
//    QPoint L2(-T/1.7,T/1.7);
//    QPoint L3(-T/1.5,T/1.5);

    double beta = 180-angle/2.0;
    double coeff1 = 1.4142/1.7;
    double coeff2 = 1.4142/1.5;

    double rotsin = sind(beta);
    double rotcos = cosd(beta);

    QPoint L1(-T*rotsin, T*cosd(beta));
    QPoint L2(-T*rotsin*coeff1,T*rotcos*coeff1);
    QPoint L3(-T*rotsin*coeff2,T*rotcos*coeff2);

    QPen linePen(Qt::yellow);
    linePen.setWidth(2);
    painter.setPen(linePen);
    painter.drawLine(L1, L2);

    painter.save();
    for(int k = 0; k < regions; k++) {
        painter.rotate(ticksAngle);
        if(k % 2 == 0) {
            painter.drawLine(L1, L3);
        }
        else
            painter.drawLine(L1, L2);
    }
    painter.restore();

    //printing speed and units
    QRectF unitLabelRect = createQRectF(QPointF(0,-80), 60, 30);
    QRectF speedLabelRect = createQRectF(QPointF(0,80), 80, 40);
    //arcPainter.drawRect(unitLabelRect);
    //arcPainter.drawRect(speedLabelRect);

    QFont speedFont;
    speedFont.setFamily("Tahoma");
    speedFont.setPointSize(14);
    speedFont.setBold(true);

    QFont unitFont;
    speedFont.setFamily("Tahoma");
    speedFont.setPointSize(20);

    painter.setPen(Qt::white);
    painter.setBrush(Qt::white);
    painter.setFont(unitFont);
    painter.drawText(unitLabelRect,Qt::AlignCenter, speed_suffixes[unitNr]);

    painter.setFont(speedFont);
    painter.drawText(speedLabelRect,Qt::AlignCenter, QString::number(val, 'f',1));

    //draw arrow
//    QPointF R1(-R/sqrt(2),-R/sqrt(2));
//    QPointF R2(R/sqrt(2), R/sqrt(2));
//    QPointF R3(-T/sqrt(2), T/sqrt(2));

//    QPointF R1(-R*rotsin,-R*rotcos);
//    QPointF R2(R*rotsin, R*rotcos);
//    QPointF R3(-T*rotsin, T*rotcos);

    QPointF R1(-R, 0);
    QPointF R2(R, 0);
    QPointF R3(0, T);

    QPointF ArrowPoints[3]={R1, R2, R3};
    QPen arrowPen(Qt::NoPen);
    QLinearGradient arrowgrad(QPoint(0,0), R3);
    arrowgrad.setColorAt(0, QColor(100, 250, 180));
    arrowgrad.setColorAt(0.6, QColor(80, 180, 20));
    arrowgrad.setColorAt(0.9,QColor(200, 230, 240));
    QBrush arrowBrush(arrowgrad);

    painter.setBrush(arrowBrush);
    painter.setPen(arrowPen);

    painter.save();
    painter.rotate(beta+val*unitSpeedAngle);
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
    for(int k = 0; k < regions + 1; k++) {
        centralPoints.push_back(QPoint(CP*cosd(stretch_angle-k*ticksAngle), -CP*sind(stretch_angle-k*ticksAngle)));
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

    //draw speed values
    QFont myFont;
    myFont.setFamily("Tahoma");
    myFont.setPointSize(14);

    int v = 0;
    for(int k = 0; k < regions + 1; k = k + 2) {
         textpainter.drawText(QRectF(centralPoints[k]-QPoint(20,20),centralPoints[k]+QPoint(20,20)),Qt::AlignCenter, QString::number(v));
         v += step;
    }

    //drawing arc
    QRadialGradient grad2(QPoint(0,0), 180);
    grad2.setColorAt(0.0, QColor(255, 255, 255, 100));
    grad2.setColorAt(0.5, QColor(0,0,250, 100));
    grad2.setColorAt(1.0, QColor(250,0,0,100));
    QPen arcPen(Qt::red);
    arcPen.setWidth(5);
    arcPen.setCapStyle(Qt::FlatCap);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(arcPen);
    painter.setBrush(grad2);
    painter.drawArc(P,stretch_angle*16-16*unitSpeedAngle*val,16*unitSpeedAngle*val);
}

void speedometer::changeValue(double newval)
{
    val = newval;
    update();
}

void speedometer::change_unitNr(int newNr)
{
    unitNr = newNr;
    update();
}

int speedometer::getStep() const
{
    return step;
}

void speedometer::setStep(int value)
{
    step = value;
    update();
}

int speedometer::getMax_speed() const
{
    return max_speed;
}

void speedometer::setMax_speed(int value)
{
    max_speed = value;
    update();
}

int speedometer::getAngle() const
{
    return angle;
}

void speedometer::setAngle(int value)
{
    angle = value;
    update();
}
