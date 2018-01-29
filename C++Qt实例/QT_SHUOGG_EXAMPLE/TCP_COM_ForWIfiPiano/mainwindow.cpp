#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTime>
#include <QHostInfo>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lineEdit->setText("333"); //端口号初始化
    ui->sendTCPButt->setEnabled(false);
    ui->lineEdit_comsend->setEnabled(false);
    ui->lineEdit_com_rec->setEnabled(false);
    ui->comsendButt->setEnabled(false);
    tcpServer=new myTcpServer(this);
    tcpClient=new myTcpClient(this);
    updateIP();//更新IP

    CurrentSerialPort = new QSerialPort(this);
    foreach(const QSerialPortInfo &SerialPortInfo,QSerialPortInfo::availablePorts())
    {
        ui->comboBox_SerialPort->addItem(SerialPortInfo.portName());
    }
    connect(CurrentSerialPort,SIGNAL(readyRead()),this,SLOT(comReadData()));

    connect(tcpServer,SIGNAL(ClientConnect(int,QString,int)),
            this,SLOT(ClientConnect(int,QString,int)));
    connect(tcpServer,SIGNAL(ClientDisConnect(int,QString,int)),
            this,SLOT(ClientDisConnect(int,QString,int)));
    connect(tcpServer,SIGNAL(ClientReadData(int,QString,int,QByteArray)),
            this,SLOT(ClientReadData(int,QString,int,QByteArray)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
/*普通函数_接收数据相关*/
void MainWindow::ReadData()
{

}
void MainWindow::ReadError(QAbstractSocket::SocketError)
{

}
/*tcp连接重要槽函数*/
void MainWindow::on_connectButt_clicked()
{
    if (ui->connectButt->text()=="connect")
    {
        bool ok=tcpServer->listen(QHostAddress::Any,ui->lineEdit->text().toInt()); //核心连接句
        if (ok)
        {
            ui->connectButt->setText("Disconnect");
            ui->statusLabel1->setText("监听成功");
            ui->sendTCPButt->setEnabled(true);
            ui->lineEdit->setEnabled(false);
        }
    }
    else
    {
        tcpServer->CloseAllClient();//断开所有已连接的客户端
        tcpServer->close();//停止监听
        ui->connectButt->setText("connect");
        ui->statusLabel1->setText("停止监听成功");
        ui->sendTCPButt->setEnabled(false);
        ui->lineEdit->setEnabled(true);
    }
}
void MainWindow::on_clearButt_clicked()
{
    ui->textEdit->clear();
}
void MainWindow::on_sendTCPButt_clicked()
{
    tcpServer->SendDataCurrent(ui->lineEdit_2->text().toLatin1());
}
/********************************客户端槽函数***************************************/
/*TCP连接核心函数之一*/
void MainWindow::ClientConnect(int clientID,QString IP,int Port)
{
    ui->statusLabel1->setText(tr("IP:%2 Port:%3 上线 ")
                              .arg(IP).arg(Port));
}

void MainWindow::ClientDisConnect(int clientID,QString IP,int Port)
{
    ui->statusLabel1->setText(tr("IP:%2 Port:%3 下线 ")
                              .arg(IP).arg(Port));
}
/*TCP接收数据核心函数*/
void MainWindow::ClientReadData(int clientID,QString IP,int Port,QByteArray data)
{
    if (!data.isEmpty())
    {

        ui->statusLabel1->setText(tr("数据:%1 来自:ID:%2 Port:%4 ")
                                  .arg(QString(data)).arg(clientID).arg(IP));
        ui->textEdit->insertPlainText(data);
        if(ui->comButt->text()=="Disconnect")
            CurrentSerialPort->write(data);

    }
}
/*更新IP的信息*/
void MainWindow::updateIP()
{
    QHostInfo info=QHostInfo::fromName(QHostInfo::localHostName());//获取此时PC用户的信息对象
    foreach (QHostAddress address, info.addresses()) {//只抽取符合ipv4协议的IP
        if(address.protocol()==QAbstractSocket::IPv4Protocol){
            ui->labelIP->setText(address.toString());
        }
    }

}



/*********************************************************************************/
/*****************************串口系列函数******************************************/
void MainWindow::on_comButt_clicked()
{
    CurrentSerialPort->setPortName(ui->comboBox_SerialPort->currentText());

    if(ui->comButt->text()=="connect")
    {   /*开串口*/
        if(CurrentSerialPort->open(QIODevice ::ReadWrite))
        {   //串口参数设置
            if(CurrentSerialPort->setBaudRate(QSerialPort ::Baud9600)
                    &&CurrentSerialPort->setDataBits(QSerialPort::Data8)
                    &&CurrentSerialPort->setDataErrorPolicy(QSerialPort::IgnorePolicy)
                    &&CurrentSerialPort->setFlowControl(QSerialPort::NoFlowControl)
                    &&CurrentSerialPort->setParity(QSerialPort::NoParity)
                    &&CurrentSerialPort->setStopBits(QSerialPort ::OneStop))

            {
                ui->statusBar->showMessage("Successful open "+CurrentSerialPort->portName());
                ui->comboBox_SerialPort->setEnabled(false);
                ui->comButt->setText("Disconnect");
                ui->lineEdit_comsend->setEnabled(true);
                ui->lineEdit_com_rec->setEnabled(true);
                ui->comsendButt->setEnabled(true);
            }

            else
            {
                ui->statusBar->showMessage("Error to open "+CurrentSerialPort->portName());
            }
        }
        else
        {
            ui->statusBar->showMessage("Error to open the "+CurrentSerialPort->portName());
        }
    }
    else
    {
        CurrentSerialPort->close();//关闭串口
        ui->statusBar->showMessage("Successful close the "+CurrentSerialPort->portName());
        ui->comboBox_SerialPort->setEnabled(true);
        ui->comButt->setText("connect");
    }

}
/*向指定串口发送数据*/
void MainWindow::on_comsendButt_clicked()
{
    QByteArray ba = ui->lineEdit_comsend->text().toLatin1();
    const char *cstr = ba.data();
    CurrentSerialPort->write(cstr);
}
/*接收com的数据,与readyRead()信号绑定*/
void MainWindow::comReadData()
{
  QByteArray data = CurrentSerialPort->readLine();
  ui->lineEdit_com_rec->setText(data);
}
