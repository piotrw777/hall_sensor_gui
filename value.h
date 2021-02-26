#ifndef VALUE_H
#define VALUE_H

#include <QObject>

class value : public QObject
{
    Q_OBJECT
public:
    explicit value(QObject *parent = nullptr);

public slots:
    void changeValue(int newval);
    void increaseValue();

signals:
    void valueChanged(int);

private:
    int myvalue;
};

#endif // VALUE_H
