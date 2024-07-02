#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QTimer>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow(); 
public slots:
    void updateTime12();
    void updateTime24();


private slots:
    void on_pushButton_change_clicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    bool format12;
};
#endif // MAINWINDOW_H
