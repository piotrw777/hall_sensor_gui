//============================================================================
// Name        : mainwindow.h
//============================================================================
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QFile>
#include <QTextStream>
#include <QSettings>

#include "thread_inc.h"
#include "unitchanger.h"
#include "button.h"
#include "value_double.h"

#define ORGANIZATION_NAME "Peter"
#define ORGANIZATION_DOMAIN "www.com"
#define APPLICATION_NAME "licznik_rowerowy"

#define EDIT_DISABLED 0
#define EDIT_RADIUS 1
#define EDIT_UNITS 2

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void send_data_to_dialog(int angle, int maxSpeed, int step);
    void edit_stateChanged(int);

protected:
    void closeEvent(QCloseEvent * event);

private slots:

void LoadSettings();
void SaveSettings();

private:
    Ui::MainWindow *ui;
    Thread_Inc thread_inc;
    int edit_state;
    QTimer * timer_radius_up;
    QTimer * timer_radius_down;
    value_double total;

private slots:
    void showDate();
    void startDialog();
    void on_pushButton_settings_clicked();
    void next_edit_state();
    void prev_unit();
    void next_unit();
    void start_radius_up();
    void start_radius_down();
    void stop_radius_up();
    void stop_radius_down();
};

#endif // MAINWINDOW_H
