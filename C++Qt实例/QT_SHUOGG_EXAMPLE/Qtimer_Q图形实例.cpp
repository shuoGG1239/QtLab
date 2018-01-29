/*****************************************************
实现的功能:
1.按下按钮butt1,子窗体逐渐透明化,但主窗体不变
2.知识点:<1>QTimer与QGraphicsEffect联合使用;
		 <2>信号与槽的自动关联和手动关联;

******************************************************/

/*----------------------------------------------------
						头文件的h
------------------------------------------------------*/
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QTimer>
#include <QDebug>
#include <QGraphicsOpacityEffect>
#include <QGraphicsEffect>

class mywidget:public QFrame
{
    Q_OBJECT
public:
    mywidget(QWidget *parent);

    QPushButton *butt1;
    QGraphicsOpacityEffect *opacityEffect;//透明效果对象
    int opalevel;       //透明等级,在透明度数组里面当指针用
public slots:
    void changeOpacity();   //普通的槽函数
    void on_bu1_clicked();  //自动关联的槽函数
};


#endif // WIDGET_H
/*---------------------------------------------
					头文件的cpp
-----------------------------------------------*/
#include "widget.h"
/*******子窗体的槽函数:自动关联bu1的clicked()信号***********/
//换成手动关联的话:connect(butt1,SIGNAL(clicked())),this,on_bu1_clicked());
void mywidget::on_bu1_clicked()
{
    QTimer *timerOpacity = new QTimer(this); //Qtimer的对象timerOpacity是信号的发出者
    connect(timerOpacity,SIGNAL(timeout()),this,SLOT(changeOpacity()));//手动关联: timer发出timerout信号由本窗体的接收并执行changeOpacity()
    timerOpacity->start(100);               //开始计时,每过完100ms都会让timer发出信号;数值会重装的,除非执行stop();
}
/*******子窗体的槽函数:改变透明度*********/
void mywidget::changeOpacity()  //每次timer计完数都会执行一次该槽函数
{
    if (opalevel > 8) return;   //当执行了9次该函数就不再执行下面的内容了,之后槽函数还是会执行,只不过卡在此处
    double opacity[10] =  {0.9,0.8,0.7,0.6,0.5,0.4,0.3,0.2,0.1,0};
    opalevel++;                 //每执行完一次就指向下一个透明度

    opacityEffect = new QGraphicsOpacityEffect;//new一个透明效果对象
    this->setGraphicsEffect(opacityEffect);     //该子窗体把透明效果对象set为自己的图形效果
    opacityEffect->setOpacity(opacity[opalevel]);//改变透明效果对象的透明参数,从而子窗体也被动着变化

    qDebug()<<"透明level = "<< opalevel <<" 子窗口透明度: "<< this->windowOpacity()<<endl;//信息输出,方便调试
}
/*********子窗体的构造函数,各种初始化**********/
 mywidget::mywidget(QWidget *parent):QFrame(parent)
{
    butt1=new QPushButton(this);
    butt1->setObjectName("bu1");
    this->setObjectName("My_First");
    this->setStyleSheet("QFrame#My_First{border-image:url(main.jpg)}");
    this->setFixedSize(800,600);
    opalevel=0;                             //透明等级初始化
    QMetaObject::connectSlotsByName(this);   //自动关联必须加这一句
}

/*-----------------------------------------------
				主函数main.cpp
--------------------------------------------------*/
#include "widget.h"
#include <QApplication>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWidget mainwindow;     //主窗口
    mywidget w(&mainwindow);//子窗体,该程序的重点对象
    mainwindow.show();      //show了主窗体,子窗体也会跟着show出来
    return a.exec();
}

