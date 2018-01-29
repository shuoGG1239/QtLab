#include "mytcpclient.h"
#include <QHostAddress>

myTcpClient::myTcpClient(QObject *parent,int clientID) :
    QTcpSocket(parent)
{    
    this->clientID=clientID;
    connect(this,SIGNAL(readyRead()),this,SLOT(ReadData()));//挂接读取数据信号
    connect(this,SIGNAL(disconnected()),this,SLOT(DisConnect()));//关闭连接时，发送断开连接信号
    //如果关闭连接自动删除，则下次不能再次监听，奇怪的问题
    //connect(this,SIGNAL(disconnected()),this,SLOT(deleteLater()));//关闭连接时，对象自动删除
}

void myTcpClient::ReadData()
{
    //读取完整一条数据并发送信号
    QByteArray data=this->readAll();
    emit ClientReadData(this->clientID,this->peerAddress().toString(),this->peerPort(),data);
}

void myTcpClient::DisConnect()
{
    //断开连接时，发送断开信号
    emit ClientDisConnect(this->clientID,this->peerAddress().toString(),this->peerPort());
}
