#include <QApplication>
#include <QPushButton>
#include <QStateMachine>
#include <QSignalTransition>
#include <QPropertyAnimation>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    QWidget *w=new QWidget;
    w->resize(240,320);                                 //建窗口

    QPushButton *button = new QPushButton("shuoGG",w);   //建按钮

    QStateMachine *machine = new QStateMachine;     //新建状态机,相当于状态的容器
    QState *state1 = new QState(machine);           //新建状态1可以用来绑定属性;状态放在状态机里面
    state1->assignProperty(button,"geometry",QRect(0,0,80,30));    //状态1绑定button的geomertry属性1
    machine->setInitialState(state1);                //state1设为初始化状态
    QState *state2 = new QState(machine);           //新建另外一个状态2
    state2->assignProperty(button,"geometry",QRect(w->width()-30,w->height()-80,30,80));//状态2绑定button的geomertry属性2

    QFont font = QFont("Airl", 12);
    state2->assignProperty(button,"font",font);     //状态2字体.1个状态可以有多种属性:本例子的状态包含:字体属性+几何属性

    QPropertyAnimation *ani=new QPropertyAnimation(button,"geometry");
    ani->setDuration(2000);
    ani->setEasingCurve(QEasingCurve::OutBounce);   //动画效果—弹跳
//addTransition()函数返回的是一个QSignalTransition型的指针
    QSignalTransition *transition1=state1->addTransition(button,SIGNAL(clicked()),state2);//动画触发信号
    transition1->addAnimation(ani);   //转变1==(button点击=(state1->state2))  //给转变1添加动画ani
    QSignalTransition *transition2=state2->addTransition(button,SIGNAL(clicked()),state1);
    transition2->addAnimation(ani);   //转变2==(button点击=(state2->state1))  //给转变2添加动画ani
    machine->start();                           //开启状态机
    w->show();
    return app.exec();
}
