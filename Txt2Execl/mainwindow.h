#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "transformthread.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_txtbtn_released();

    void on_execlbtn_released();

    void on_startbtn_released();

    void thread_started();

    void thread_stopped();

private:
    Ui::MainWindow *ui;
    TransformThread *convert;
};

#endif // MAINWINDOW_H
