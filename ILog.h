/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/04/13
**   File: ILog.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_ILOG_H
#define IMODULE_ILOG_H

#include "IModule.h"

namespace iris
{
class ILog : public IModule
{
private:      
      ILog(const ILog &module) ;

      ILog& operator = (const ILog &module) ;
protected:
      ILog() {}
public:
    virtual ~ILog() {}
      
    static SmartPtr<ILog> singleton() ;
  
	/**
	 * 初始化模块内部参数，启动线程等
	 */
	virtual int init(const char *folder)=0;

	/**
	 * 退出模块内部线程，释放内存等
	 */
	virtual int exit()=0;

	/**
	 * 退出模块内部线程，释放内存等
	 */
	virtual int write(const char* module , int levelid , const char *format , ...)=0;   

    virtual const char*  getClassName() const { return "ILog" ;} 
};



#ifndef ILOG

#define ILOG_INIT(LOG_FILE_PATH) \
        ILog::singleton()->init(LOG_FILE_PATH)
 
#define ILOG(MODULE_NAME , LEVEL_ID , FMT...) \
        ILog::singleton()->write(MODULE_NAME , LEVEL_ID , FMT)

#define ILOG_EXIT()     \
        ILog::singleton()->exit() 

#endif

}  // namespace iris
#endif
