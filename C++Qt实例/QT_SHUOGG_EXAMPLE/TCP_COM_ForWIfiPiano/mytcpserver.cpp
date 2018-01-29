#include "mytcpserver.h"
#include <QHostAddress>

myTcpServer::myTcpServer(QObject *parent) :
    QTcpServer(parent)
{
    this->clientCount=0;
}

void myTcpServer::incomingConnection(int handle)
{
    myTcpClient *client=new myTcpClient(this,handle);
    client->setSocketDescriptor(handle);

    connect(client,SIGNAL(ClientReadData(int,QString,int,QByteArray)),this,SIGNAL(ClientReadData(int,QString,int,QByteArray)));
    connect(client,SIGNAL(ClientDisConnect(int,QString,int)),this,SLOT(DisConnect(int,QString,int)));

    emit ClientConnect(handle, client->peerAddress().toString(),client->peerPort());

    ClientList.append(client);//将新的连接添加到客户端列表
    ClientID.append(handle);//将新的连接的ID添加到客户端ID列表
    clientCount++;

    //存储当前连接
    CurrentClient=client;
}

void myTcpServer::DisConnect(int clientID,QString IP,int Port)
{
    for (int i=0;i<clientCount;i++)
    {
        if (ClientID[i]==clientID)
        {
            ClientList.removeAt(i);//从列表中移除该连接
            ClientID.removeAt(i);
            clientCount--;
            i--;//不然的话，永远只会移除第一个连接
            emit ClientDisConnect(clientID,IP,Port);
            break;
        }
    }
}

//指定客户端连接发消息
void myTcpServer::SendData(int clientID, QByteArray data)
{
    for (int i=0;i<clientCount;i++)
    {
        if (ClientID[i]==clientID)
        {
            ClientList[i]->write(data);
            break;
        }
    }
}

//对当前连接发送数据
void myTcpServer::SendDataCurrent(QByteArray data)
{
    //如果没有一个存在的连接，则不处理
    if (clientCount<1){return;}
    CurrentClient->write(data);
}

//对所有连接发送数据
void myTcpServer::SendDataAll(QByteArray data)
{
    for (int i=0;i<clientCount;i++)
    {
        ClientList[i]->write(data);
    }
}

void myTcpServer::CloseAllClient()
{
    for (int i=0;i<clientCount;i++)
    {
        ClientList[i]->close();
        i--;//不然的话，永远只会断开第一个连接
    }
}
