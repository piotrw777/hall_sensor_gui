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

#define ORGANIZATION_NAME "Peter"
#define ORGANIZATION_DOMAIN "www.com"
#define APPLICATION_NAME "licznik_rowerowy"

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

protected:
    void closeEvent(QCloseEvent * event);
private slots:

void LoadSettings();
void SaveSettings();

private:
    Ui::MainWindow *ui;
    Thread_Inc thread_inc;
    //unitChanger unitchgr;

private slots:
    void showDate();
    void startDialog();
    void on_pushButton_settings_clicked();
};

#endif // MAINWINDOW_H
