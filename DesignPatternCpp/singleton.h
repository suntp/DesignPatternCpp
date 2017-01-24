/************************************
name:suntp
time:16.12.28
email:605682931@qq.com
***********************************/

#pragma once

#include <iostream>
#include <memory>
#include <Windows.h>
using namespace std;
/***************************************************************************************

1������Ҫ��һ������ʵ���ľ�̬����GetInstance
2��ʵ�ֵķ�ʽ�ȿ���ͨ��new��̬������Ҳ����ͨ��static��̬�ֲ�����ʵ��
3��������ʱ���ȿ���ͨ����̬������ʼ��ʱ������Ҳ�����ڵ���GetInstance����ʱ�ٴ���,ͨ����̬�����ĳ�ʼ���ĺô���
�����ڽ���������֮ǰ�����ɹ��Ŀ��Ա�����̵߳����⣬���ǻ��������ڳ�������ʱ��ʼ���������������̡�
4��Ϊ�˷�ֹͨ�����ù��캯������ʵ����Ҫ����Ĺ��졢���ƹ���͸�ֵ���캯����Ϊ˽�е�
5��GetInstance�����ķ���ֵ�ȿ�����ָ�룬�ֿ��������ã�����ָ���ʱ��Ҫ��ֹ������;��delete�������Ҫ������������Ϊ˽�е�
6������ģʽ�е���ȫ�ֱ�����������������ģ������������Ǳ�ֻ֤��һ��ʵ�������ܹ�ȫ�ַ������������Ĺ��ܡ�

********************************************************//////////////////////////////////////
class singleton1
{
public:
	static singleton1* GetInstance()
	{
		if(ptr == NULL)
			ptr = new singleton1;
		return ptr;
	}

	static void show()
	{
		cout << "singleton1::show" << endl;
	}

private:
	~singleton1()
	{
		cout << "dest singleton1" << endl;
	}
	static singleton1* ptr;
	singleton1()
	{
		cout << "cstr singleton1" << endl;
	}

	singleton1(const singleton1 &);
	singleton1& operator=(const singleton1 &);
};

singleton1* singleton1::ptr = new singleton1;

/*****************
1���������ʵ���У�ʹ��ָ��ʱ����������ʵ����ֻ�е��������ʱ����ϵͳ���գ����ǽ�ָ����Ƴ�����ָ��shared_ptr��
��������ָ��Ļ��ջ���Ҫ������������������Ϊpublic��ָ����ʱ�ᱻdelete���кܶ����⣬�������ַ����ǲ�̫ʵ��
*****************/
class singleton3
{
public:
	~singleton3()
	{
		cout << "dest singleton3" << endl;
	}

	static singleton3* GetInstance()
	{
		if(ptr.get() == NULL)
			ptr.reset(new singleton3);
		return ptr.get();
	}

	static void show()
	{
		cout << "singleton3::show" << endl;
	}

private:
	static shared_ptr<singleton3> ptr;
	singleton3(){}
	singleton3(const singleton3 &);
	singleton3& operator=(const singleton3 &);
};

shared_ptr<singleton3> singleton3::ptr;

/****************************************
1�������ʵ�ֶ��ǻ���new��̬���������ҷ��صĶ���ָ�����ͣ����ʵ�ֻ��ھ�̬�ֲ����������ҷ�����������
2���������ö�����ָ��ĺô��ǣ����õ����м�ᱻdelete��
3�����þ�̬�ֲ������ĺô��ǣ��ڴ������ϵͳ������Ҫ�ֶ�����
****************************************/
class singleton4
{
public:
	~singleton4()
	{
		cout << "dest singleton4" << endl;
	}

	static singleton4& GetInstance()
	{
		static singleton4 s;
		return s;
	}

	static void show()
	{
		cout << "singleton4::show" << endl;
	}

private:
	singleton4(){;}
	singleton4(const singleton4 &);
	singleton4& operator=(const singleton4 &);
};

/***************************
1���������GetInstance�����д���ʵ���������Ƕ��̵߳Ļ�������ж���߳�ͬʱ���øú�����
����ܻᴴ�����ʵ��������Ҫ�Դ������̽��м�������
**************************/
CRITICAL_SECTION g_cs;
class Lock
{
public:
	Lock()
	{
		InitializeCriticalSection(&g_cs);
	}

	void LockOn()
	{
		EnterCriticalSection(&g_cs);
	}

	void LockOff()
	{
		LeaveCriticalSection(&g_cs);
	}

	~Lock()
	{
		DeleteCriticalSection(&g_cs);
	}
};
Lock g_lock;

class singleton5
{
public:
	~singleton5()
	{
		cout << "dest singleton5" << endl;
	}

	static singleton5* GetInstance()
	{
		if(ptr == NULL)
		{
			//����˫���ж���Ϊ�����Ч�ʣ���ֹÿ�ζ�Ҫִ�м�������
			g_lock.LockOn();
			if(ptr == NULL)
				ptr = new singleton5;
			g_lock.LockOff();
		}

		return ptr;
	}

	static void show()
	{
		cout << "singleton5::show" << endl;
	}

private:
	static singleton5* ptr;
	singleton5(){}
	singleton5(const singleton5 &);
	singleton5& operator=(const singleton5 &);
};
singleton5* singleton5::ptr = NULL;

/******************
1�������ʵ����Ȼ�����˶��̵߳��ã�����ʵ���п��ܻ��кܶ��඼Ҫ��Ƴ�ʵ��ģʽ��
��ô����Ҫ��������������ʵ��һ�飬�������ã������ģ����Ϳ����������õ�����
*******************************/
template <typename T>
class Singleton
{
public:
	static T& Instance()
	{
		if (m_pInstance == NULL)
		{
			//Lock lock;
			g_lock.LockOn();
			if (m_pInstance == NULL)
			{
				m_pInstance = new T;
				atexit(&Destroy);//��Destroyע��Ϊ�������ʱ��ִ�к����ͷ��ڴ�
			}

			//return *m_pInstance;
			g_lock.LockOff();
		}

		return *m_pInstance;
	}

protected:
	Singleton(void) 
	{
		cout << "cstr Singleton" << endl;
	}
	virtual ~Singleton(void) 
	{
		cout << "dest Singleton" << endl;
	}

private:
	Singleton(const Singleton& rhs)
	{
		cout << "copy cstr Singleton" << endl;
	}
	Singleton& operator = (const Singleton& rhs) 
	{
		cout << "= cstr Singleton" << endl;
	}

	static void Destroy()
	{
		if (m_pInstance != NULL)
			delete m_pInstance;
		m_pInstance = NULL;
	}

	static T* m_pInstance;
};

template <typename T>
T* Singleton<T>::m_pInstance = NULL;

//ʵ�ʵĵ�����Ͱ�������ķ�ʽʵ��
class SingletonInstance : public Singleton<SingletonInstance>
{
public:
	friend Singleton<SingletonInstance>;
	void show()
	{
		cout << "SingletonInstance::show" << endl;
	}
//
private:
	SingletonInstance() 
	{
		cout << "cstr SingletonInstance" << endl;
	}
	virtual ~SingletonInstance(void) 
	{
		cout << "dest SingletonInstance" << endl;
	}

	SingletonInstance(const SingletonInstance& rhs) 
	{
		cout << "copy cstr SingletonInstance" << endl;
	}
};

//������
class SingletonTest
{
public:
	SingletonTest()
	{
		//singleton1& s1 = singleton1::GetInstance1();
		//s1.show();

		//singleton1 *p1 = singleton1::GetInstance();
		//p1->show();
		////delete p1;

		//singleton3 *p3 = singleton3::GetInstance();
		//p3->show();

		//singleton4 &p4 = singleton4::GetInstance();
		//p4.show();

		//singleton5 *p5 = singleton5::GetInstance();
		//p5->show();

		SingletonInstance &si = SingletonInstance::Instance();
		si.show();
	}
};