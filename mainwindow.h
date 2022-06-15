#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>
#include <QTimer>

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

    void on_action_2_triggered();

    void on_action_3_triggered();

private:
    Ui::MainWindow *ui;
    int width;
    int height;
};
#endif // MAINWINDOW_H
