#ifndef MYTCPSERVER_H
#define MYTCPSERVER_H
#include <QTcpServer>
#include "mytcpclient.h"

class myTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit myTcpServer(QObject *parent = 0);
    void SendData(int clientID, QByteArray data);
    void SendDataCurrent(QByteArray data);
    void SendDataAll(QByteArray data);

    int ClientCount()const{return clientCount;}
    void CloseAllClient();

private:
    QList<myTcpClient *> ClientList;
    QList<int> ClientID;
    myTcpClient *CurrentClient;

    int clientCount;

protected:
    void incomingConnection(int handle);

signals:
    void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
    void ClientConnect(int clientID,QString IP,int Port);
    void ClientDisConnect(int clientID,QString IP,int Port);

private slots:
    void DisConnect(int clientID,QString IP,int Port);

public slots:

};

#endif // MYTCPSERVER_H
