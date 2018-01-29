/*-----------------------------------------
引用是被引用者的别名,本身不占内存,主要功能用于传参,
 其免复制特性使得用函数时减少内存消耗并提高速度;
 引用和"&的取地址"是完全两回事!
 ---------------------------------------------*/
#include <iostream>
#include <stddef.h>
using namespace std;
class A
{
public:
    int a;	//4个字节
    int b;	//4个字节
};

void change1(const A &gg) //(还可以写成(const A& gg))
{
 // gg.a+=10;  //const的作用就是,引用无法修改原对象.所以这两句会报错
 // gg.b+=33;  //相当于const将引用变为只读
    cout<<gg.a<<" "; //就算有const,不能改动,但能读
    cout<<sizeof(gg); //引用只是被引用者的别名,此处输出8
}
void change2(A gg)//普通传参
{
    gg.a+=10;
    gg.b+=33;
}
void change3(A& gg)//引用传参
{
    gg.a+=10;
    gg.b+=33;
}

int main()
{
    A shuogg;
    shuogg.a=0;
    shuogg.b=0;
    cout<<sizeof(shuogg);//输出:8 (说明shuogg不是指针,而是一个大数据块)
    change1(shuogg);    //输出:0 8(说明引用也不是指针,而是shuogg的别名)
    change2(shuogg);//此函数就是先复制一份shuogg到gg,执行完函数后释放,无法修改shuogg的a,b值
    cout<<shuogg.a<<" "<<shuogg.b<<" ";//输出:0 0
    change3(shuogg);//引用传参不会复制的,功能和指针相似,故函数结束可以改动shuogg
    cout<<shuogg.a<<" "<<shuogg.b<<" ";//输出:10 33
    return 0;
}

