/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/27
**   File: IMSurfaceManager.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_IM_SURFACE_MANAGER_H
#define IMODULE_IM_SURFACE_MANAGER_H


#include "IModule.h"

#include <memory>


namespace iris
{
class IMSurfaceManager : public virtual IModule
{
protected:
      IMSurfaceManager() {}
private:      
      IMSurfaceManager(const IMSurfaceManager &module) ;
      
      IMSurfaceManager& operator = (const IMSurfaceManager &module) ;
      
public:

      static SmartPtr<IMSurfaceManager>& singleton() ;
      
      virtual ~IMSurfaceManager() {}
	/**
	 * 初始化模块内部参数，启动线程等
	 */
	virtual int init()=0;
      virtual const char*  getClassName() const { return "IMSurfaceManager" ;}      
     /**
	 * 此后为SurfaceManager通用接口函数
	 */
      
};

}  // namespace iris
#endif
