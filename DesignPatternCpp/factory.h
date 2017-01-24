/************************************
name:suntp
time:17.01.08
email:605682931@qq.com
***********************************/
#pragma once

#include <iostream>
using namespace std;

/**************************************************************
工厂模式分为简单工厂模式、工厂方法模式和抽象工厂模式
简单工厂模式有三种类：抽象产品类，具体产品类，具体工厂类。具体产品类派生于抽象产品类，
可以有很多种，工厂类只有一个，所有的的产品都由这个工厂类生产，里面有创建产品的函数。
但是有一个问题就是，每新增一种产品后，就需要修改这个工厂类，导致这个工厂类需要被频繁修改。
而开放封闭修改的原则就是“类可以扩展，不能修改”。简单工厂不符合这个原则，所以就有了工厂方法模式。
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
1、工厂方法模式有四种类：抽象产品类，具体产品类，抽象工厂类，具体工厂类。
2、具体工厂类不是生产所有产品，一个具体工厂类只用于生产一种产品。
3、每增加一个具体产品类，就增加一个对应的具体工厂类
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

抽象工厂模式也有四种类：抽象产品类，具体产品类，抽象工厂类，具体工厂类。
但是有很多个抽象产品类，而这些抽象产品类之间相互组合就可以产生更多的具体产品，
如果现在还是每种产品对应一个具体工厂类，那么工厂类的数目就会很多。
此时就需要对具体工厂类进行分类，根据一个抽象产品类的分类确定具体工厂类的种类，
里面再提供不同的创建不同子产品类的接口。但是又有一个问题，如果出现类新的产品类，
那么就要扩展新的具体工厂类，或者增加具体工厂类里面的接口种类，尽量设计成扩展新的具体工厂类。

工厂方法模式和抽象工厂模式的类的种类虽然是一样的，但是抽象产品类的数目却不一样，工厂方法模式只有一个，
抽象工厂是多个，这也是这两种模式的最根本区别。并且工厂方法模式的具体工厂类只对应产生一种具体产品。
抽象工厂模式的一个具体工厂类却可以产生多个具体产品。

各工厂模式的缺点
1、简单工厂模式违反了开放封闭原则，不利于扩展类，只能修改现有类。
2、工厂方法模式中，如果具体产品发生变化，就需要修改对应的具体工厂，但出现新的抽象产品类时，就更麻烦了。
3、抽象工厂模式中，如果出现了新的抽象产品类，很难扩展。

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

//各工厂模式测试类
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