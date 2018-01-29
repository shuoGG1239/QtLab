#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mytcpclient.h"
#include "mytcpserver.h"
#include <QDebug>
#include <QSerialPort>
#include <QListWidget>
#include <QQueue>
#include <QByteArray>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSerialPort *CurrentSerialPort;
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateIP();


private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpClient;
    myTcpServer *tcpServer;
signals:
    void ReceiveBufferReady();

private slots:

    //客户端槽函数
    void ReadData();
    void ReadError(QAbstractSocket::SocketError);
    //服务端槽函数
    void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
    void ClientConnect(int clientID,QString IP,int Port);
    void ClientDisConnect(int clientID,QString IP,int Port);
    void on_connectButt_clicked();
    void on_clearButt_clicked();
    //com系列槽函数
    void on_sendTCPButt_clicked();
    void comReadData();
    void on_comsendButt_clicked();
    void on_comButt_clicked();

};

#endif // MAINWINDOW_H
