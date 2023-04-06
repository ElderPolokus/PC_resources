#ifndef CONF_CONNECTION_H
#define CONF_CONNECTION_H

#include <QDialog>

namespace Ui {
class conf_connection;
}

class conf_connection : public QDialog
{
    Q_OBJECT

public:
    explicit conf_connection(QString send_IP, int send_Port, QWidget *parent = nullptr);
    ~conf_connection();

private slots:
    void on_Accept_clicked();

    void on_Escape_clicked();

    void slotChangeConfigConnectPort(int ch_Port);

    void slotChangeConfigConnectIP(QString ch_IP);

private:
    Ui::conf_connection *ui;
    int Port;
    QString IP;

signals:
    void sendConfig(QString IP, int port);
};

#endif // CONF_CONNECTION_H
