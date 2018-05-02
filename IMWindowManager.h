/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/27
**   File: IMWindowManager.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_IM_WINDOW_MANAGER_H
#define IMODULE_IM_WINDOW_MANAGER_H


#include "IModule.h"

#include <memory>

namespace iris
{
class IMWindowManager : public virtual IModule
{
protected:
      IMWindowManager() {}
private:      
      IMWindowManager(const IMWindowManager &module) ;

      IMWindowManager& operator = (const IMWindowManager &module) ;

public:
      
      static SmartPtr<IMWindowManager>& singleton() ;

      virtual ~IMWindowManager() {}
	/**
	 * 初始化模块内部参数，启动线程等
	 */
	virtual int init()=0;
      virtual const char*  getClassName() const { return "IMWindowManager" ;}
     /**
	 * 此后为IWindowManager通用接口函数
	 */
};

}  // namespace iris
#endif
