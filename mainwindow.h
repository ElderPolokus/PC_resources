#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void timer();

    void on_action_Image_PC_triggered();

    void on_action_Image_Printer_triggered();

    void on_action_Image_Laptop_triggered();

    void on_action_Image_Server_triggered();

    void on_action_UserInfo_triggered();

private:
    Ui::MainWindow *ui;
    int width;
    int height;
};
#endif // MAINWINDOW_H
