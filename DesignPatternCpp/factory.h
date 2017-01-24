/************************************
name:suntp
time:17.01.08
email:605682931@qq.com
***********************************/
#pragma once

#include <iostream>
using namespace std;

/**************************************************************
����ģʽ��Ϊ�򵥹���ģʽ����������ģʽ�ͳ��󹤳�ģʽ
�򵥹���ģʽ�������ࣺ�����Ʒ�࣬�����Ʒ�࣬���幤���ࡣ�����Ʒ�������ڳ����Ʒ�࣬
�����кܶ��֣�������ֻ��һ�������еĵĲ�Ʒ������������������������д�����Ʒ�ĺ�����
������һ��������ǣ�ÿ����һ�ֲ�Ʒ�󣬾���Ҫ�޸���������࣬���������������Ҫ��Ƶ���޸ġ�
�����ŷ���޸ĵ�ԭ����ǡ��������չ�������޸ġ����򵥹������������ԭ�����Ծ����˹�������ģʽ��
**************************************************************/
class SingleCore
{
public:
	virtual ~SingleCore(){};
	virtual void Show() = 0;
};

class SingleCoreA : public SingleCore
{
public:
	~SingleCoreA(){};
	virtual void Show()
	{
		cout << "SingleCoreA::Show" << endl;
	}
};

class SingleCoreB : public SingleCore
{
public:
	~SingleCoreB(){};
	virtual void Show()
	{
		cout << "SingleCoreB::Show" << endl;
	}
};

typedef enum ClassType  
{  
	SINGCORE_A,  
	SINGCORE_B,   
}CoreType;  

class SimpleFactory
{
public:
	~SimpleFactory(){};
	SingleCore* CreateCores(CoreType cType)
	{
		if (cType == SINGCORE_A)
		{
			return new SingleCoreA;
		}
		else if (cType == SINGCORE_B)
		{
			return new SingleCoreB;
		}
	}
};

/*******************************************
1����������ģʽ�������ࣺ�����Ʒ�࣬�����Ʒ�࣬���󹤳��࣬���幤���ࡣ
2�����幤���಻���������в�Ʒ��һ�����幤����ֻ��������һ�ֲ�Ʒ��
3��ÿ����һ�������Ʒ�࣬������һ����Ӧ�ľ��幤����
******************************************/
class FactoryBase
{
public:
	virtual ~FactoryBase(){};
	virtual SingleCore* CreateCores() = 0;
};

class FactoryA : public FactoryBase
{
public:
	virtual ~FactoryA(){};
	virtual SingleCore* CreateCores()
	{
		return new SingleCoreA;
	}
};

class FactoryB : public FactoryBase
{
public:
	virtual ~FactoryB(){};
	virtual SingleCore* CreateCores()
	{
		return new SingleCoreB;
	}
};

/*******************************************************

���󹤳�ģʽҲ�������ࣺ�����Ʒ�࣬�����Ʒ�࣬���󹤳��࣬���幤���ࡣ
�����кܶ�������Ʒ�࣬����Щ�����Ʒ��֮���໥��ϾͿ��Բ�������ľ����Ʒ��
������ڻ���ÿ�ֲ�Ʒ��Ӧһ�����幤���࣬��ô���������Ŀ�ͻ�ܶࡣ
��ʱ����Ҫ�Ծ��幤������з��࣬����һ�������Ʒ��ķ���ȷ�����幤��������࣬
�������ṩ��ͬ�Ĵ�����ͬ�Ӳ�Ʒ��Ľӿڡ���������һ�����⣬����������µĲ�Ʒ�࣬
��ô��Ҫ��չ�µľ��幤���࣬�������Ӿ��幤��������Ľӿ����࣬������Ƴ���չ�µľ��幤���ࡣ

��������ģʽ�ͳ��󹤳�ģʽ�����������Ȼ��һ���ģ����ǳ����Ʒ�����Ŀȴ��һ������������ģʽֻ��һ����
���󹤳��Ƕ������Ҳ��������ģʽ����������𡣲��ҹ�������ģʽ�ľ��幤����ֻ��Ӧ����һ�־����Ʒ��
���󹤳�ģʽ��һ�����幤����ȴ���Բ�����������Ʒ��

������ģʽ��ȱ��
1���򵥹���ģʽΥ���˿��ŷ��ԭ�򣬲�������չ�ֻ࣬���޸������ࡣ
2����������ģʽ�У���������Ʒ�����仯������Ҫ�޸Ķ�Ӧ�ľ��幤�����������µĳ����Ʒ��ʱ���͸��鷳�ˡ�
3�����󹤳�ģʽ�У�����������µĳ����Ʒ�࣬������չ��

***********************************************************************************/

class MultiCore
{
public:
	virtual ~MultiCore(){};
	virtual void Show() = 0;
};

class MultiCoreA : public MultiCore
{
public:
	virtual ~MultiCoreA(){};
	virtual void Show()
	{
		cout << "MultiCoreA::Show" << endl;
	}
};

class MultiCoreB : public MultiCore
{
public:
	virtual ~MultiCoreB(){};
	virtual void Show()
	{
		cout << "MultiCoreB::Show" << endl;
	}
};

class AbstractFactory
{
public:
	virtual ~AbstractFactory(){};

	virtual SingleCore* CreateSingleCore() = 0;
	virtual MultiCore* CreateMultiCore() = 0;
};

class AbstractFactoryA : public AbstractFactory
{
public:
	virtual ~AbstractFactoryA(){};

	virtual SingleCore* CreateSingleCore()
	{
		return new SingleCoreA;
	}
	virtual MultiCore* CreateMultiCore()
	{
		return new MultiCoreA;
	}
};

class AbstractFactoryB : public AbstractFactory
{
public:
	virtual ~AbstractFactoryB(){};

	virtual SingleCore* CreateSingleCore()
	{
		return new SingleCoreB;
	}
	virtual MultiCore* CreateMultiCore()
	{
		return new MultiCoreB;
	}
};

//������ģʽ������
class FactoryTest
{
public:
	FactoryTest()
	{
		SimpleFactory sf;
		SingleCore *pSC = sf.CreateCores(SINGCORE_A);
		pSC->Show();
		pSC = sf.CreateCores(SINGCORE_B);
		pSC->Show();

		FactoryA fa;
		pSC = fa.CreateCores();
		pSC->Show();

		FactoryB fb;
		pSC = fb.CreateCores();
		pSC->Show();

		MultiCore *pMC;
		AbstractFactoryA afa;
		pSC = afa.CreateSingleCore();
		pSC->Show();
		pMC = afa.CreateMultiCore();
		pMC->Show();
	}
};