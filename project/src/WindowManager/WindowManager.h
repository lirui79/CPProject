/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/28
**   File: WindowManager.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_WINDOW_MANAGER_H
#define IMODULE_WINDOW_MANAGER_H


#include "IMWindowManager.h"
#include "IStatus.h"

namespace iris
{
class WindowManager : public IMWindowManager , public IMStatus
{
private:
      WindowManager() ;    
      WindowManager(const WindowManager &module) ;

      WindowManager& operator = (const WindowManager &module) ;

public:
      
      static SmartPtr<WindowManager>& singleton() ;

      virtual ~WindowManager() ;

      virtual const char*  getClassName() const { return "WindowManager" ;}
	/**
	* 初始化模块内部参数，启动线程等
	*/
	virtual int init() ;

	/**
	* 退出模块内部线程，释放内存等
	*/
	virtual int exit() ;     
     /**
	 * 此后为IWindowManager通用接口函数
	 */
};

}  // namespace iris
#endif
