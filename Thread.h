/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/30
**   File: Thread.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef DELEGATE_THREAD_H
#define DELEGATE_THREAD_H

#include "SmartObject.h"
#include "SmartPtr.h"
#include <pthread.h>

namespace iris
{

	// 接口基类
	class IDelegate : public virtual SmartObject
	{
	public:
		virtual int Invoke() = 0;//执行虚函数
	};

	//无参数函数 接口类
	template<typename T>
	class IDelegate0 : public IDelegate
	{
	protected:
        int (T::*pfun)() ;      //无参数函数
		SmartPtr<T>  t ;   //类型实体对象指针
	public:
		IDelegate0( T *_t, int (T::*_pfun)()) : pfun(_pfun), t(_t) 
		{			}

		IDelegate0(SmartPtr<T>  &_t, int (T::*_pfun)()) : pfun(_pfun), t(_t) 
		{			}

		int Invoke()
		{
			return ((*t).*pfun)() ;
		}

        virtual const char*  getClassName() const { return "IDelegate0";}
	};

	//有一个参数函数 接口类 
	template<typename T , typename P1>
	class IDelegate1 : public IDelegate
	{	
	protected:
		int (T::*pfun)(P1) ;		//有一个参数函数 
		SmartPtr<T>        t ;		//实体对象指针
		P1                p1 ;		//参数
	public:
		IDelegate1( T *_t, int (T::*_pfun)(P1) , const P1 &_p1 ) : pfun(_pfun), t(_t) , p1(_p1)
		{			}

		IDelegate1(SmartPtr<T> &_t, int (T::*_pfun)(P1) , const P1 &_p1 ) : pfun(_pfun), t(_t)  , p1(_p1)
		{			}

		int Invoke()
		{
			return ((*t).*pfun)(p1) ;
		}

		void Set(const P1 &_p1) 
		{
			p1 = _p1 ;
		}

        virtual const char*  getClassName() const { return "IDelegate1";}
	};

	//有两个参数函数 接口类
	template<typename T , typename P1 , typename P2>
	class IDelegate2 : public IDelegate
	{
	protected:
		int (T::*pfun)(P1 , P2) ;//有两个参数函数 
		SmartPtr<T>        t ;		//实体对象指针
		P1                p1 ;		//第一个参数
		P2                p2 ;		//第二个参数
	public:
		IDelegate2( T *_t, int (T::*_pfun)(P1 , P2) , const P1 &_p1 , const P2 &_p2  ) : pfun(_pfun), t(_t) , p1(_p1) , p2(_p2)
		{			}

		IDelegate2(SmartPtr<T>  &_t, int (T::*_pfun)(P1 , P2) , const P1 &_p1 , const P2 &_p2  ) : pfun(_pfun), t(_t)  , p1(_p1) , p2(_p2)
		{			}

		int Invoke()
		{
			return ((*t).*pfun)(p1 , p2) ;
		}

		void Set(const P1 &_p1 , const P2 &_p2) 
		{
			p1 = _p1 ;
			p2 = _p2 ;
		}

        virtual const char*  getClassName() const { return "IDelegate2";}
	};

	//有三个参数函数 接口类
	template<typename T , typename P1 , typename P2 , typename P3>
	class IDelegate3 : public IDelegate
	{
	protected:
		int (T::*pfun)(P1 , P2 , P3) ;		//有三个参数函数 
		SmartPtr<T>         t ;		            //实体对象指针
		P1                p1 ;			        //第一个参数	
		P2                p2 ;		            //第二个参数		
		P3                p3 ;   	            //第三个参数
	public:
		IDelegate3( T *_t, int (T::*_pfun)(P1 , P2 , P3) , const P1 &_p1 , const P2 &_p2  , const P3 &_p3  ) : pfun(_pfun), t(_t) , p1(_p1) , p2(_p2) , p3(_p3)
		{			}

		IDelegate3(SmartPtr<T> &_t, int (T::*_pfun)(P1 , P2 , P3) , const P1 &_p1 , const P2 &_p2  , const P3 &_p3  ) : pfun(_pfun), t(_t)  , p1(_p1) , p2(_p2) , p3(_p3)
		{			}

		int Invoke()
		{
			return ((*t).*pfun)(p1 , p2 , p3) ;
		}

		void Set(const P1 &_p1, const P2 &_p2, const P3 &_p3) 
		{
			p1 = _p1 ;
			p2 = _p2 ;
			p3 = _p3 ;
		}

        virtual const char*  getClassName() const { return "IDelegate3";}
};

//线程类型
	class Thread : public virtual SmartObject
	{
	private :
		Thread(const Thread &thread);
		Thread& operator = (const Thread &thread) ;
	public :
		Thread() : pIDelegate(NULL){}
        
		Thread(IDelegate *_pIDelegate ) : pIDelegate(_pIDelegate)
		{
			Start() ;
		}

		virtual ~Thread() 
		{	}

        void Start(IDelegate *_pIDelegate)  
		{
			pIDelegate.reset(_pIDelegate) ;
			Start() ;
		}

		unsigned long Wait(unsigned long ms)
		{
			return 0x00 ;
		}

        virtual const char*  getClassName() const { return "Thread";}
	protected :

		void Start()
		{
			pthread_t  pthreadId ;
			pthread_create(&pthreadId, NULL, &ThreadRun, this);
			pthread_detach(pthreadId);
		}

		static void *ThreadRun(void *pTHREAD) 
		{
			Thread* pThread = (Thread*) (pTHREAD) ;
			pThread->ThreadRun() ;
			return pThread ;
		}

		void ThreadRun()
		{
			if(pIDelegate.get() == NULL)
				return ;
			pIDelegate->Invoke() ;
			pIDelegate.reset(NULL) ;
		}

	protected :
		SmartPtr<IDelegate>  pIDelegate ;
	};
}

#endif
