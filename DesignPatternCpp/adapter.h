/************************************
name:suntp
time:17.01.05
email:605682931@qq.com
***********************************/
#pragma once

#include <iostream>
using namespace std;

/******************************************************************

���ڵ�ǰ�ṩ�ӿڲ���������Ҫ�Ľӿڣ���Ҫ�Ե�ǰ�ӿڽ��з�װת������������

������ģʽ���漰�Ľ�ɫ������
Ŀ�꣨Target����ɫ�����ǿͻ����ڴ��Ľӿڡ�
Դ��Adaptee����ɫ����Ҫ������ࡣ
��������Adapter����ɫ����Դ�ӿ�ת����Ŀ��ӿ�,��һ��ɫ��������.

������ģʽ��Ϊ���������Ͷ�����������
���������ķ�ʽ�ǲ��ö�̳еķ�ʽ����adaptorͬʱ�̳�target��adaptee��
�����������ķ�ʽ�ǲ������ڶ���ʽ��adaptor�̳���target��
ͬʱ��adaptee������Ϊadaptor��Ϊ���������һ����Ա����ͨ�������ýӿں�����

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

//������ģʽ������
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
