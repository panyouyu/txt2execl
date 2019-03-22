#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qfiledialog.h"
#include "qmessagebox.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setValue(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_txtbtn_released()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("txt (*.txt *.log)"));
    ui->inputlabel->setText(fileName);
    ui->inputlabel->setToolTip(fileName);
}

void MainWindow::on_execlbtn_released()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "/home",
                                                    tr("xlsx (*.xlsx)"));
    ui->outputlabel->setText(fileName);
    ui->outputlabel->setToolTip(fileName);
}

void MainWindow::on_startbtn_released()
{
    if(!QFile::exists(ui->inputlabel->text()) || !QFile::exists(ui->outputlabel->text()))
    {
        QMessageBox::information(this, tr("tip"), QStringLiteral("文件不存在"));
        return ;
    }
    convert = new TransformThread(this, ui->inputlabel->text(), ui->outputlabel->text());
    connect(convert, SIGNAL(started()), this, SLOT(thread_started()));
    connect(convert, SIGNAL(finished()), this, SLOT(thread_stopped()));
    connect(convert, SIGNAL(total(int)), ui->progressBar, SLOT(setMaximum(int)));
    connect(convert,SIGNAL(current(int)), ui->progressBar, SLOT(setValue(int)));
    convert->start();
}

void MainWindow::thread_started()
{
    ui->startbtn->setEnabled(false);
}

void MainWindow::thread_stopped()
{
    ui->startbtn->setEnabled(true);
    convert->deleteLater();
    QMessageBox::information(this, tr("tip"), QStringLiteral("转换完成"));
}
