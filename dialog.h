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
private:
    Ui::Dialog *ui;
    int angle;
    int maxSpeed;
    int step;
};

#endif // DIALOG_H
