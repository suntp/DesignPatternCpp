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
������ģʽ������stl�еĵ�����������������˳��������ݽṹ���������Ԫ�أ��õ�Ԫ���׵�ַ����ǰָ��Ԫ�ء�
���ڿռ����������ݽṹ�������ܹ�˳������⣬���ܹ�������ʵĹ��ܡ�����Ҫ�����ࣺ
1����������࣬��������Ҫ�Ľӿں���������˵��ȡ��ǰλ��Ԫ�أ���λ�����õ���ʼλ�ã���λ��ָ����һλ�á�
2����������࣬ʵ������������Ľӿں�����
3�����������࣬�������ݶ����һ��ӿڡ����紴��������
4����������࣬�����ʵ�ֳ��ýӿڣ���������ĳ��λ�ã�[]�������Ԫ�س��ȵȡ�
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

//������ģʽ������
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

