#pragma once

#include<iostream>
#include<set>
#include<string>
using namespace std;

/////////////////////抽象模式定义
class CObservable;

//观察者，纯虚基类
class CObserver
{
public:
	CObserver::CObserver(){};
	virtual CObserver::~CObserver(){};
	//当被观察的目标发生变化时，通知调用该方法
	//来自被观察者pObs,扩展参数为pArg
	virtual void Update(CObservable* pObs,void* pArg = NULL) = 0;
};

//被观察者，即Subject
class CObservable
{
public:
	CObservable() : m_bChanged(false){};
	virtual ~CObservable(){};

	//注册观察者
	void Attach(CObserver *pObs);

	//注销观察者
	void Detach(CObserver *pObs);

	//注销所有观察者
	void DetachAll();

	//若状态变化，则遍历观察者，逐个通知更新
	void Notify(void*pArg=NULL);

	//测试目标状态是否变化
	bool HasChanged();

	//获取观察者数量
	int GetObserversCount();

protected:
	//设置状态变化!!!必须继承CObservable才能设置目标状态
	void SetChanged();

	//初始化目标为未变化状态
	void ClearChanged();

private:
	bool m_bChanged;//状态
	set<CObserver*> m_setObs;//set保证目标唯一性
};

/////////////////////抽象模式实现
void CObservable::Attach(CObserver* pObs)
{
	if(!pObs)
		return;
	m_setObs.insert(pObs);
}

void CObservable::Detach(CObserver* pObs)
{
	if(!pObs)
		return;
	m_setObs.erase(pObs);
}

void CObservable::DetachAll()
{
	m_setObs.clear();
}

void CObservable::SetChanged()
{
	m_bChanged = true;
}
void CObservable::ClearChanged()
{
	m_bChanged = false;
}
bool CObservable::HasChanged()
{
	return m_bChanged;
}
int CObservable::GetObserversCount()
{
	return m_setObs.size();
}
void CObservable::Notify(void* pArg/*=NULL*/)
{
	if(!HasChanged())
		return;
	cout << "notify observers…" << endl;
	ClearChanged();
	set<CObserver*>::iterator itr = m_setObs.begin();
	for(; itr != m_setObs.end(); itr++)
	{
		(*itr)->Update(this, pArg);
	}
}

/////////////////////具体应用类定义和实现
//bloger是发布者，即被观察者(subject)
class CBloger : public CObservable
{
public:
	void Publish(const string& strContent)
	{
		cout << "bloger publish,content:" << strContent << endl;
		SetChanged();
		Notify(const_cast<char*>(strContent.c_str()));
	}
};

//portal是发布者，即被观察者(subject)
class CPortal : public CObservable
{
public:
void Publish(const string& strContent)
{
	cout << "portal publish, content:" << strContent << endl;
	SetChanged();
	Notify(const_cast<char*>(strContent.c_str()));
}
};

			 //RSS阅读器，观察者
class CRSSReader : public CObserver
{
public:
	CRSSReader(const string& strName) : m_strName(strName){}
	virtual void Update(CObservable* pObs,void* pArg = NULL)
	{
		char* pContent = static_cast<char*>(pArg);
		//观察多个目标
		if(dynamic_cast<CBloger*>(pObs))
		{
			cout << m_strName << "updated from bloger,content:" << pContent << endl;
		}
		else if(dynamic_cast<CPortal*>(pObs))
		{
			cout << m_strName << "updated from portal,content:" << pContent << endl;
		}
	}
private:
	string m_strName;
};

//Mail阅读器，观察者
class CMailReader : public CObserver
{
public:
	CMailReader(const string& strName) : m_strName(strName){}
	virtual void Update(CObservable* pObs, void* pArg = NULL)
	{
		char* pContent = static_cast<char*>(pArg);
		if(dynamic_cast<CBloger*>(pObs))
		{
			cout << m_strName << "updated from bloger,content:" << pContent << endl;
		}
		if(dynamic_cast<CPortal*>(pObs))
		{
			cout << m_strName << "updated from portal,content:" << pContent << endl;
		}
	}
private:
	string m_strName;
};

class ObserverTest
{
public:
	ObserverTest()
	{
		//目标(被观察者)
		CBloger* pBloger = new CBloger();
		CPortal* pPortal = new CPortal();
	
		//观察者.一个观察者可以观察多个目标
		CRSSReader* pRssReader = new CRSSReader("rss reader");
		CMailReader* pMailReader = new CMailReader("mail reader");
	
		pBloger->Attach(pRssReader);//bloger注册观察者
		pBloger->Attach(pMailReader);//bloger注册观察者
		pPortal->Attach(pRssReader);//portal注册观察者
		pPortal->Attach(pMailReader);//portal注册观察者
	
		//博客发布信息
		pBloger->Publish("博客分享设计模式");
		cout << endl;
	
		//门户发布信息
		pPortal->Publish("门户分享设计模式");
	
		cout << "\nportal detached mail reader" << endl;
		pPortal->Detach(pMailReader);
		cout << "portal observers count:" << pPortal->GetObserversCount() << endl << endl;
	
		pPortal->Publish("门户分享设计模式");
	}
};
