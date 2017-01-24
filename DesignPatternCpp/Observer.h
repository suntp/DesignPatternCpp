#pragma once

#include<iostream>
#include<set>
#include<string>
using namespace std;

/////////////////////����ģʽ����
class CObservable;

//�۲��ߣ��������
class CObserver
{
public:
	CObserver::CObserver(){};
	virtual CObserver::~CObserver(){};
	//�����۲��Ŀ�귢���仯ʱ��֪ͨ���ø÷���
	//���Ա��۲���pObs,��չ����ΪpArg
	virtual void Update(CObservable* pObs,void* pArg = NULL) = 0;
};

//���۲��ߣ���Subject
class CObservable
{
public:
	CObservable() : m_bChanged(false){};
	virtual ~CObservable(){};

	//ע��۲���
	void Attach(CObserver *pObs);

	//ע���۲���
	void Detach(CObserver *pObs);

	//ע�����й۲���
	void DetachAll();

	//��״̬�仯��������۲��ߣ����֪ͨ����
	void Notify(void*pArg=NULL);

	//����Ŀ��״̬�Ƿ�仯
	bool HasChanged();

	//��ȡ�۲�������
	int GetObserversCount();

protected:
	//����״̬�仯!!!����̳�CObservable��������Ŀ��״̬
	void SetChanged();

	//��ʼ��Ŀ��Ϊδ�仯״̬
	void ClearChanged();

private:
	bool m_bChanged;//״̬
	set<CObserver*> m_setObs;//set��֤Ŀ��Ψһ��
};

/////////////////////����ģʽʵ��
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
	cout << "notify observers��" << endl;
	ClearChanged();
	set<CObserver*>::iterator itr = m_setObs.begin();
	for(; itr != m_setObs.end(); itr++)
	{
		(*itr)->Update(this, pArg);
	}
}

/////////////////////����Ӧ���ඨ���ʵ��
//bloger�Ƿ����ߣ������۲���(subject)
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

//portal�Ƿ����ߣ������۲���(subject)
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

			 //RSS�Ķ������۲���
class CRSSReader : public CObserver
{
public:
	CRSSReader(const string& strName) : m_strName(strName){}
	virtual void Update(CObservable* pObs,void* pArg = NULL)
	{
		char* pContent = static_cast<char*>(pArg);
		//�۲���Ŀ��
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

//Mail�Ķ������۲���
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
		//Ŀ��(���۲���)
		CBloger* pBloger = new CBloger();
		CPortal* pPortal = new CPortal();
	
		//�۲���.һ���۲��߿��Թ۲���Ŀ��
		CRSSReader* pRssReader = new CRSSReader("rss reader");
		CMailReader* pMailReader = new CMailReader("mail reader");
	
		pBloger->Attach(pRssReader);//blogerע��۲���
		pBloger->Attach(pMailReader);//blogerע��۲���
		pPortal->Attach(pRssReader);//portalע��۲���
		pPortal->Attach(pMailReader);//portalע��۲���
	
		//���ͷ�����Ϣ
		pBloger->Publish("���ͷ������ģʽ");
		cout << endl;
	
		//�Ż�������Ϣ
		pPortal->Publish("�Ż��������ģʽ");
	
		cout << "\nportal detached mail reader" << endl;
		pPortal->Detach(pMailReader);
		cout << "portal observers count:" << pPortal->GetObserversCount() << endl << endl;
	
		pPortal->Publish("�Ż��������ģʽ");
	}
};
