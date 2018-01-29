#include <vector>
#include <iostream>
using namespace std;

template<typename T1>
class slotbase
{
public:
	virtual void Execute(T1 para) = 0;
};

template<typename T, typename T1>
class slotimpl : public slotbase<T1>
{
public:
	slotimpl(T* pObj, void (T::*pMemberFunc)(T1))
	{
		m_pObj = pObj;
		m_pMemberFunc = pMemberFunc;
	}
	virtual void Execute(T1 para)
	{
		(m_pObj->*m_pMemberFunc)(para);
	}
private:
	T* m_pObj;
	void (T::*m_pMemberFunc)(T1);
};

template<typename T1>
class slot
{
public:
	template<typename T>
	slot(T* pObj, void (T::*pMemberFunc)(T1))
	{
		m_pSlotbase = new slotimpl<T, T1>(pObj, pMemberFunc);
	}
	~slot()
	{
		delete m_pSlotbase;
	}
	void Execute(T1 para)
	{
		m_pSlotbase->Execute(para);
	}
private:
	slotbase<T1>* m_pSlotbase;
};

template<typename T1>
class signal
{
public:
	template<typename T>
	void bind(T* pObj, void (T::*pMemberFunc)(T1 para))
	{
		m_slots.push_back(new slot<T1>(pObj, pMemberFunc));
	}
	~signal()
	{
		vector<slot<T1>* >::iterator ite = m_slots.begin();
		for (; ite != m_slots.end(); ite++)
		{
			delete *ite;
		}
	}
	void operator()(T1 para)
	{
		vector<slot<T1>* >::iterator ite = m_slots.begin();
		for (; ite != m_slots.end(); ite++)
		{
			(*ite)->Execute(para);
		}
	}

private:
	vector<slot<T1>* > m_slots;
};

#define CONNECT(sender,signal,receiver,slot)  sender.signal.bind(receiver,slot)

class receiver
{
public:
	void callback1(int a)
	{
		cout << "receiver1: " << a << endl;
	}
};
class receiver2
{
public:
	void callback2(int a)
	{
		cout << "receiver2: " << a << endl;
	}
};

class sender
{
public:
	sender() : m_value(0)  {}
	int get_value()
	{
		return m_value;
	}
	void set_value(int new_value)
	{
		if (new_value != m_value)
		{
			m_value = new_value;
			m_valueChanged(new_value);
		}
	}
	signal<int> m_valueChanged;
private:
	int m_value;

};

int main(int argc, char** arg)
{
	receiver r;
	receiver2 r2;
	sender s;
	CONNECT(s, m_valueChanged, &r, &receiver::callback1);
	CONNECT(s, m_valueChanged, &r2, &receiver2::callback2);
	s.set_value(1);
	system("pause");
	return 0;
}

