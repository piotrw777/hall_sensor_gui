#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    int getAngle() const;
    int getMaxSpeed() const;
    int getStep() const;

public slots:
    void setPresentValues(int angleVal, int maxSpeedVal, int stepVal);

signals:
    void angleChanged(int);
    void maxSpeedChanged(int);
    void stepChanged(int);

private slots:
    void on_pushButton_OK_clicked();
    void on_pushButton_Cancel_clicked();

    void setAngle(int value);
    void setMaxSpeed(int value);
    void setStep(int value);
    void restore_values();

private:
    Ui::Dialog *ui;
    int present_angle;
    int present_maxSpeed;
    int present_step;
    int angle;
    int maxSpeed;
    int step;
};

#endif // DIALOG_H
