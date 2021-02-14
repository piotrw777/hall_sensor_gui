#ifndef CIRCLE_H
#define CIRCLE_H

#include <QWidget>

class circle : public QWidget
{
    Q_OBJECT
public:
    explicit circle(QWidget *parent = nullptr);
    ~circle(){}

protected:
    void paintEvent(QPaintEvent *event);

signals:

public slots:
    void changeValue(double);

private:
    double val;
};



#endif // CIRCLE_H
