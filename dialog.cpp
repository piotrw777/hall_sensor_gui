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
    QObject::connect(this,&Dialog::rejected, this, &Dialog::restore_values);

    QObject::connect(&left_button_counter, SIGNAL(valueChanged(int)), ui->lcd_left_button, SLOT(display(int)));
    QObject::connect(&right_button_counter, SIGNAL(valueChanged(int)), ui->lcd_right_button, SLOT(display(int)));
    QObject::connect(&main_button_counter, SIGNAL(valueChanged(int)), ui->lcd_main_button, SLOT(display(int)));
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

void Dialog::restore_values()
{
    this->angle = present_angle;
    this->maxSpeed = present_maxSpeed;
    this->step = present_step;
}

void Dialog::setPresentValues(int angleVal, int maxSpeedVal, int stepVal)
{
    ui->spinBox_Angle->setValue(angleVal);
    ui->spinBox_MaxSpeed->setValue(maxSpeedVal);
    ui->spinBox_Step->setValue(stepVal);
    present_angle = angleVal;
    present_maxSpeed = maxSpeedVal;
    present_step = stepVal;
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
