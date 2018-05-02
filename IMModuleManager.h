/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/27
**   File: IMModuleManager.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_IMMODULE_MANAGER_H
#define IMODULE_IMMODULE_MANAGER_H

#include "IModule.h"

#include <memory>


namespace iris
{
class IMModuleManager : public virtual IModule
{
protected:
	IMModuleManager() ;
private:
	IMModuleManager(const IMModuleManager &module) ;

	IMModuleManager& operator = (const IMModuleManager &module) ;
      
public:

    static SmartPtr<IMModuleManager> singleton() ;

	virtual ~IMModuleManager() ;
	/**
	 * 初始化模块内部参数，启动线程等
	 */
	virtual int init()=0;
    virtual const char*  getClassName() const { return "IMModuleManager" ;}        
};

}  // namespace iris
#endif
