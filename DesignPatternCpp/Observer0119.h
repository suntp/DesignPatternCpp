/************************************
name:suntp
time:17.01.19
email:605682931@qq.com
***********************************/
#pragma once

#include <iostream>
#include <set>
using namespace std;

/*************************************************************

观察者模式（有时又被称为发布（publish ）-订阅（Subscribe）模式、模型-视图（View）模式、源-收听者(Listener)模式或从属者模式）,
在此种模式中，一个目标物件管理所有相依于它的观察者物件，并且在它本身的状态改变时主动发出通知。
这通常透过呼叫各观察者所提供的方法来实现。此种模式通常被用来实现事件处理系统。

好处：将观察者与被观察者分开处理，便于管理
缺点：如果一个被观察者有很多观察者，那么将通知全部发给各观察者需要很长时间

观察者模式有很多实现方式，从根本上说，该模式必须包含两个角色：观察者和被观察对象。
再具体是抽象观察者和被观察者，具体观察者和被观察者。实现观察者模式的时候要注意，
观察者和被观察对象之间的互动关系不能体现成类之间的直接调用，否则就将使观察者和被观察对象之间紧密的耦合起来，
从根本上违反面向对象的设计的原则。无论是观察者“观察”观察对象，还是被观察者将自己的改变“通知”观察者，
都不应该直接调用。因此具体被观察者里面维护的观察者列表的类型是抽象观察者，并且抽象观察者中包含一个统一的通知接口，
供被观察者调用通知每一个具体的观察者，其实就是利用了基类和继承类的虚函数调用。

实现观察者模式有很多形式，比较直观的一种是使用一种“注册——通知——撤销注册”的形式。
观察者（Observer）将自己注册到被观察对象（Subject）中，被观察对象将观察者存放在一个容器（Container）里。
观察者模式被观察，被观察对象发生了某种变化（如图中的SomeChange），从容器中得到所有注册过的观察者，将变化通知观察者。
观察者告诉被观察者要撤销观察，被观察者从容器中将观察者去除。

观察者将自己注册到被观察者的容器中时，被观察者不应该过问观察者的具体类型，而是应该使用观察者的接口。
这样的优点是：假定程序中还有别的观察者，那么只要这个观察者也是相同的接口实现即可。
一个被观察者可以对应多个观察者，当被观察者发生变化的时候，他可以将消息一一通知给所有的观察者。
基于接口，而不是具体的实现——这一点为程序提供了更大的灵活性。

关于消息推送有两种实现方式
“推”的方式是指，Subject维护一份观察者的列表，每当有更新发生，Subject会把更新消息主动推送到各个Observer去。
“拉”的方式是指，各个Observer维护各自所关心的Subject列表，自行决定在合适的时间去Subject获取相应的更新数据。
“推”的好处包括：
1、高效。如果没有更新发生，不会有任何更新消息推送的动作，即每次消息推送都发生在确确实实的更新事件之后，都是有意义的。
2、实时。事件发生后的第一时间即可触发通知操作。
3、可以由Subject确立通知的时间，可以避开一些繁忙时间。
4、可以表达出不同事件发生的先后顺序。
“拉”的好处包括：
1、如果观察者众多，Subject来维护订阅者的列表，可能困难，或者臃肿，把订阅关系解脱到Observer去完成。
2、Observer可以不理会它不关心的变更事件，只需要去获取自己感兴趣的事件即可。
3、Observer可以自行决定获取更新事件的时间。
4、拉的形式可以让Subject更好地控制各个Observer每次查询更新的访问权限。
事实上“推”和“拉”可以比较的内容太多了，比如：
客户端通常是不稳定的，服务端是稳定的，如果消息由客户端主动发起去获取，它很容易找到服务端的地址，可以比较容易地做到权限控制（集中在服务端一处），服务端也可以比较容易地跟踪客户端的位置和状态，反之则不行；
互联网页面的访问就是一个最好的“拉”的模式的例子；
通常我们希望把压力分散到各个客户端上去，服务端只做最核心的事情，只提供内容，不管理分发列表；
还有一个idea是关于“推”和“拉”结合的形式，例如，服务端只负责通知某一些数据已经准备好，至于是否需要获取和什么时候客户端来获取这些数据，完全由客户端自行确定。

****************************************************************************************************************/

class CObservable;

class CObserver
{
public:
	virtual ~CObserver(){};
	virtual void Update(CObservable* pObs, void* pArg = NULL) = 0;
};

class CObservable
{
public:
	virtual ~CObservable(){};
	void AddObserver(CObserver* p)
	{
		m_SetObservers.insert(p);
	}

	void DelObserver(CObserver* p)
	{
		m_SetObservers.erase(p);
	}

	void Notify(void* pArg = NULL)
	{
		set<CObserver*>::iterator itr = m_SetObservers.begin();
		for (; itr != m_SetObservers.end(); ++itr)
		{
			(*itr)->Update(this, pArg);
		}
	}

private:
	set<CObserver*> m_SetObservers;
};

class CPublisher : public CObservable
{
public:
	void Publish()
	{
		Notify("new contents");
	}
};

class CListener : public CObserver
{
public:
	void Update(CObservable* pObs, void* pArg = NULL)
	{
		char* pContent = static_cast<char*>(pArg);

		if(dynamic_cast<CPublisher*>(pObs))
		{
			cout << "Listener get " << "update from Publisher,content:" << pContent << endl;
		}
	}
};

class ObserverTest
{
public:
	ObserverTest()
	{
		CListener listen1;
		CPublisher publisher1;
		publisher1.AddObserver(&listen1);
		publisher1.Publish();
		publisher1.DelObserver(&listen1);
		publisher1.Publish();
	}
};