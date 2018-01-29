#include <iostream>
#include <stdio.h>
using namespace std;

class Base
{
private:
	 void display()
	{
		cout << "Base display()" << endl;
	}
	void say()
	{
		cout << "Base say()" << endl;
	}
public:
	void exec()
	{
		display();
		say();
	}
	void f1(string a)
	{
		cout << "Base f1(string)" << endl;
	}
	void f1(int a)
	{
		cout << "Base f1(int)" << endl;
	} //overload，两个f1函数在Base类的内部被重载
};

class DeriveA: public Base
{
public:
	void display()
	{
		cout << "DeriveA display()" << endl;
	} //override，基类中display为虚函数，故此处为重写
	void f1(int a, int b)
	{
		cout << "DeriveA f1(int,int)" << endl;
	} //redefining，f1函数在Base类中不为虚函数，故此处为重定义
	void say()
	{
		cout << "DeriveA say()" << endl;
	} //redefining，同上
};

class DeriveB: public Base
{
public:
	void f1(int a)
	{
		cout << "DeriveB f1(int)" << endl;
	} //redefining，重定义
};

int main()
{
	DeriveA a;
	Base *base = &a;
	base->exec();
    //)b里边的函数display被A类覆盖，但是say还是自己的。
	a.exec(); //same result as last statement

	a.say();

	DeriveB b;
	b.f1(1); //version of DeriveB called
}
