#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QTime>
#include <QApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Some Window Modificatoins

    setWindowTitle("Digital Clock");
    setWindowIcon(QIcon(":/rec/images/clk.png"));

    resize(430, 200); // Set initial size to 800x600 pixels

    QScreen *primaryScreen = QGuiApplication::primaryScreen();
    QRect screenGeometry = primaryScreen->geometry();
    int x = screenGeometry.width() - width();
    int y = 0;

    // Set initial position
    move(x, y); // Move to the top-right corner of the screen


    //######################################

    // Timer for updating the time each second

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime24()));
    timer->start(1000);

    //######################################
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updateTime12()
{
    format12 = true;
    QTime time = QTime::currentTime();
    QString stringTime = time.toString("hh : mm : ss");
    if (time.hour() > 12) {
        QString newHours = QString::number(time.hour() - 12);
        stringTime.replace(0, 2, newHours);
    }
    ui->label_time->setText(stringTime);
}

void MainWindow::updateTime24()
{
    format12 = false;
    QTime time = QTime::currentTime();
    QString stringTime = time.toString("hh : mm : ss");
    ui->label_time->setText(stringTime);
}

void MainWindow::on_pushButton_change_clicked()
{
    if (format12){
        disconnect(timer, SIGNAL(timeout()), this, SLOT(updateTime12()));
        connect(timer, SIGNAL(timeout()), this, SLOT(updateTime24()));
        ui->pushButton_change->setText("Display in 12 hr Format");
    }

    else {
        disconnect(timer, SIGNAL(timeout()), this, SLOT(updateTime24()));
        connect(timer, SIGNAL(timeout()), this, SLOT(updateTime12()));
        ui->pushButton_change->setText("Display in 24 hr Format");
    }

}

