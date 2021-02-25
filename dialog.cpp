#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    QObject::connect(ui->spinBox_Angle, SIGNAL(valueChanged(int)),this, SLOT(setAngle(int)));
    QObject::connect(ui->spinBox_MaxSpeed, SIGNAL(valueChanged(int)),this, SLOT(setMaxSpeed(int)));
    QObject::connect(ui->spinBox_Step, SIGNAL(valueChanged(int)),this, SLOT(setStep(int)));
}

Dialog::~Dialog()
{
    delete ui;
}
void Dialog::setAngle(int value)
{
    if(value != angle)
    {
        angle = value;
        emit angleChanged(value);
    }

}
void Dialog::setMaxSpeed(int value)
{
    if(value != maxSpeed)
    {
        maxSpeed = value;
        emit maxSpeedChanged(value);
    }
}
void Dialog::setStep(int value)
{
    if(value != step && (maxSpeed % value == 0))
    {
        step = value;
        emit stepChanged(value);
    }
}

//get functions
int Dialog::getAngle() const
{
    return angle;
}
int Dialog::getMaxSpeed() const
{
    return maxSpeed;
}
int Dialog::getStep() const
{
    return step;
}

void Dialog::on_pushButton_OK_clicked()
{
    this->accept();
}

void Dialog::on_pushButton_Cancel_clicked()
{
    this->reject();
}
