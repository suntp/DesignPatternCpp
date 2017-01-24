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

1、首先要有一个创建实例的静态函数GetInstance
2、实现的方式既可以通过new动态创建，也可以通过static静态局部变量实现
3、创建的时机既可以通过静态变量初始化时创建，也可以在调用GetInstance函数时再创建,通过静态变量的初始化的好处是
它是在进入主函数之前创建成功的可以避免多线程的问题，但是坏处就是在程序启动时初始化会拖慢启动过程。
4、为了防止通过调用构造函数创建实例，要将类的构造、复制构造和赋值构造函数设为私有的
5、GetInstance函数的返回值既可以是指针，又可以是引用，当是指针的时候要防止它在中途被delete掉，因此要将析构函数设为私有的
6、这种模式有点像全局变量，但还是有区别的，单件的作用是保证只有一份实例，而能够全局访问是它附带的功能。

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
1、在上面的实现中，使用指针时，不能销毁实例，只有当程序结束时才由系统回收，考虑将指针设计成智能指针shared_ptr，
但是智能指针的回收还是要调用析构函数，声明为public，指针随时会被delete，有很多问题，所以这种方法是不太实用
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
1、上面的实现都是基于new动态创建，并且返回的都是指针类型，这个实现基于静态局部变量，并且返回引用类型
2、返回引用而不是指针的好处是，不用担心中间会被delete掉
3、采用静态局部变量的好处是，内存管理交给系统，不需要手动管理
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
1、如果是在GetInstance函数中创建实例，并且是多线程的话，如果有多个线程同时调用该函数，
则可能会创建多个实例，所以要对创建过程进行加锁处理
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
			//采用双重判断是为了提高效率，防止每次都要执行加锁过程
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
1、上面的实现虽然满足了多线程调用，但是实际中可能会有很多类都要设计成实例模式，
那么就需要都按照上面那样实现一遍，不能重用，下面的模板类就可以满足重用的需求
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
				atexit(&Destroy);//将Destroy注册为程序结束时的执行函数释放内存
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

//实际的单例类就按照下面的方式实现
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

//测试类
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