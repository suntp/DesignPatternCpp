/************************************
name:suntp
time:17.01.02
email:605682931@qq.com
***********************************/
#pragma once

#include <iostream>
#include <vector>
using namespace std;

/*****************************************************************
迭代器模式，就像stl中的迭代器，利用它可以顺序访问数据结构里面的所有元素，得到元素首地址，当前指向元素。
对于空间连续的数据结构，除了能够顺序访问外，还能够随机访问的功能。这需要四种类：
1、抽象迭代类，定义所需要的接口函数，比如说获取当前位置元素，将位置重置到开始位置，将位置指向下一位置。
2、具体迭代类，实现上面所定义的接口函数。
3、抽象数据类，定义数据对象的一般接口。比如创建迭代器
4、具体对象类，定义和实现常用接口，包括访问某个位置，[]运算符，元素长度等。
**************************************************************************/

template<class Item>
class BaseIterator
{
public:
	virtual ~BaseIterator(){};
	virtual void First() = 0;
	virtual void Next() = 0;
	virtual Item& CurrentItem() = 0;
};

template<class Item>
class BaseAggregate
{
public:
	virtual ~BaseAggregate(){};
	virtual BaseIterator<Item>* CreateIterator() = 0;
	virtual Item& GetIndexItem(int nIndex) = 0;
	virtual int GetLength() = 0;
};

template<class Item>
class ConcreteIterator : public BaseIterator<Item>
{
public:
	ConcreteIterator(BaseAggregate<Item>* p):
	m_pBA(p),
	m_current(0)
	{

	}

	virtual void First()
	{
		m_current = 0;
	}
	virtual void Next()
	{
		++m_current;
	}
	virtual Item& CurrentItem()
	{
		return m_pBA->GetIndexItem(m_current);
	}

private:
	int m_current;
	BaseAggregate<Item>* m_pBA;
};

template<class Item>
class ConcreteAggregate : public BaseAggregate<Item>
{
public:
	ConcreteAggregate()
	{
		m_vecInt.push_back(1);
		m_vecInt.push_back(2);
		m_vecInt.push_back(3);
	}
	virtual BaseIterator<Item>* CreateIterator()
	{
		return new ConcreteIterator<Item>(this);
	}

	virtual Item& GetIndexItem(int nIndex)
	{
		return m_vecInt[nIndex];
	}

	Item& operator[](int nIndex)
	{
		return m_vecInt[index];
	}

	int GetLength()
	{
		return m_vecInt.size();
	}

private:
	vector<int> m_vecInt;
};

//迭代器模式测试类
class IteratorTest
{
public:
	IteratorTest()
	{
		BaseAggregate<int>* pBA = new ConcreteAggregate<int>();
		BaseIterator<int> *pBI = pBA->CreateIterator();

		for (int i = 0; i < pBA->GetLength(); ++i)
		{
			cout << pBI->CurrentItem() << endl;
			pBI->Next();
		}

		delete pBI;
		delete pBA;
	}
};

