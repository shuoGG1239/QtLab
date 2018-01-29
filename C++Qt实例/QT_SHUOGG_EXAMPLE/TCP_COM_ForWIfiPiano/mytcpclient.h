#ifndef MYTCPCLIENT_H
#define MYTCPCLIENT_H

#include <QTcpSocket>

class myTcpClient : public QTcpSocket
{
    Q_OBJECT
public:
    explicit myTcpClient(QObject *parent = 0,int clientID=0);

private:
    int clientID;
    
signals:
    void ClientReadData(int clientID,QString IP,int Port,QByteArray data);
    void ClientDisConnect(int clientID,QString IP,int Port);
    
private slots:
    void ReadData();
    void DisConnect();

public slots:

};

#endif // MYTCPCLIENT_H
