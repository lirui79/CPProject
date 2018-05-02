/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/20
**   File: ModuleManager.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_MODULE_MANAGER_H
#define IMODULE_MODULE_MANAGER_H

#include "IMModuleManager.h"
#include "IMWindowManager.h"
#include "IStatus.h"

#include <list>
#include <memory>
#include <map>

namespace iris
{
class ModuleManager : public IMModuleManager , public IMStatus {
private:
	std::list<SmartPtr<IModule> >   mModules;
	SmartPtr<IMWindowManager>       mWindowManager ;
private:
	ModuleManager() ;

	ModuleManager(const ModuleManager &module) ;

	ModuleManager& operator = (const ModuleManager &module) ;
      
public:
      
	static SmartPtr<ModuleManager>& singleton() ;

	virtual ~ModuleManager() ;

    virtual const char*  getClassName() const { return "ModuleManager" ;}    
	/**
	* 初始化模块内部参数，启动线程等
	*/
	virtual int init() ;

	/**
	* 退出模块内部线程，释放内存等
	*/
	virtual int exit() ;

	SmartPtr<IMWindowManager>&  getWindowManager() ;
};

}  // namespace iris
#endif
