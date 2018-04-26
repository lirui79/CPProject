/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/04/13
**   File: Log.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_LOG_H
#define IMODULE_LOG_H

#include "ILog.h"
#include "Mutex.h"
#include "Thread.h"
#include "IStatus.h"
#include <list> 

namespace iris
{
class Log : public ILog , public IMStatus {
private:
    class item {
       public:
         item() ;
         ~item() ;
       char mStrLog[1024] ;
       int  mLogLevel ;
    } ;

    std::list<item*> mLogs ;
    char            mFolder[64] ;
    char            mFileName[256] ;
    Mutex           mLMutex ;
    Event           mLEvent ;
    Mutex           mEMutex ;
    Event           mEEvent ;
    SmartPtr<Thread>  mThread ;
private:      
      Log(const Log &module) ;

      Log& operator = (const Log &module) ;
protected:
      Log() ;
      int writelog() ;
public:
    virtual ~Log() ;
      
    static SmartPtr<Log>& singleton() ;
  
	/**
	 * 初始化模块内部参数，启动线程等
	 */
	virtual int init(const char *folder);

	/**
	 * 退出模块内部线程，释放内存等
	 */
	virtual int exit();

	/**
	 * 退出模块内部线程，释放内存等
	 */
	virtual int write(const char* module, int levelid , const char *format , ...);   


    virtual int run() ;

    virtual const char*  getClassName() const { return "Log" ;} 
};

}  // namespace iris
#endif
