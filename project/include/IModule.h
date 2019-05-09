/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/20
**   File: IModule.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_I_MODULE_H
#define IMODULE_I_MODULE_H

#include "SmartObject.h"
#include "SmartPtr.h"

namespace iris
{
class IModule : public virtual SmartObject
{
public:    
    virtual ~IModule() {
    }
	/**
	 * 初始化模块内部参数，启动线程等
	 */
	//virtual int init()=0;

	/**
	 * 退出模块内部线程，释放内存等
	 */
	virtual int exit()=0;

    virtual const char*  getClassName() const { return "IModule" ;} 
};

struct ModuleInfo {
	/** version info for the module */
	const char* version;

	/** name of this module */
	const char* name;

	/** padding to 128 bytes, reserved for future use */
	const char* reserved[32 - 2];
};

}  // namespace iris
#endif
