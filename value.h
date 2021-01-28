#ifndef VALUE_H
#define VALUE_H

#include <QObject>
class MainWindow;
class value : public QObject
{
    Q_OBJECT
public:
    friend class MainWindow;
    explicit value(QObject *parent = nullptr);

signals:
    void valueChanged(int);

public slots:
    void setValue(int newValue);

private:
    int myValue;

};

#endif // VALUE_H
