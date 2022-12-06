#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const QString& strHost, int nPort, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
//    void slotReadyRead();

    void slotError(QAbstractSocket::SocketError);

//    void slotSendToServer();

//    void slotConnected();

    void timer();

    void on_action_Image_PC_triggered();

    void on_action_Image_Printer_triggered();

    void on_action_Image_Laptop_triggered();

    void on_action_Image_Server_triggered();

    void on_action_UserInfo_triggered();

    void on_action_ConnectToServer_triggered();

private:
    Ui::MainWindow *ui;
    int width;
    int height;
    QTcpSocket* m_pTcpSocket;
    quint16 m_nNextBlockSize;
};
#endif // MAINWINDOW_H
