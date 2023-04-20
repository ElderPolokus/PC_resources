#ifndef PC_RESOURCES_H
#define PC_RESOURCES_H

#include <QMainWindow>
#include <QTcpSocket>

QT_BEGIN_NAMESPACE
namespace Ui { class pc_resources; }
QT_END_NAMESPACE

class pc_resources : public QMainWindow
{
    Q_OBJECT

public:
    pc_resources(QWidget *parent = nullptr);
    ~pc_resources();

private slots:
    void slotError(QAbstractSocket::SocketError);

    void slotSendToServer();

    void slotConnected();

    void slotDisconnected();

    void timer();

    void getImage(int sel);

    void on_action_Image_PC_triggered();

    void on_action_Image_Printer_triggered();

    void on_action_Image_Laptop_triggered();

    void on_action_Image_Server_triggered();

    void on_action_UserInfo_triggered();

    void on_action_ConnectToServer_triggered();

    void on_Configure_connection_triggered();

public slots:
    void getConfigChange(QString IP, int port);

    QString getIPHost();

private:
    Ui::pc_resources *ui;
    int width;
    int height;
    QTcpSocket* m_pTcpSocket;
    quint16 m_nNextBlockSize;

public:
    int cpu_res;
    int ram_res;
    QString disk_name;
    int disk_res;
    int Port = 2323;
    QString IP = "0.0.0.0";
};
#endif // PC_RESOURCES_H
