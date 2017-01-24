/************************************
name:suntp
time:17.01.05
email:605682931@qq.com
***********************************/
#pragma once

#include <iostream>
using namespace std;

/******************************************************************

用于当前提供接口不满足所需要的接口，需要对当前接口进行封装转化以满足需求

适配器模式所涉及的角色包括：
目标（Target）角色：这是客户所期待的接口。
源（Adaptee）角色：需要适配的类。
适配器（Adapter）角色：把源接口转换成目标接口,这一角色必须是类.

适配器模式分为类适配器和对象适配器。
类适配器的方式是采用多继承的方式，将adaptor同时继承target和adaptee。
对象适配器的方式是采用类内对象方式，adaptor继承自target，
同时将adaptee对象作为adaptor作为它类里面的一个成员对象，通过它调用接口函数。

******************************************************************/

class target
{
public:
	virtual ~target(){};
	virtual void show() = 0;
};

class adatpee
{
public:
	~adatpee(){};
	void display()
	{
		cout << "display" << endl;
	}
};

class AdaptorObject : public target, private adatpee
{
public:
	void show()
	{
		display();
	}
};

class AdaptorClass : public target
{
public:
	void show()
	{
		ae.display();
	}

private:
	adatpee ae;
};

//适配器模式测试类
class AdapterTest
{
public:
	AdapterTest()
	{
		AdaptorObject ao;
		ao.show();

		AdaptorClass ac;
		ac.show();
	}
};
