/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/28
**   File: SurfaceManager.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_SURFACE_MANAGER_H
#define IMODULE_SURFACE_MANAGER_H


#include "IMSurfaceManager.h"
#include "IStatus.h"
#include <memory>


namespace iris
{
class SurfaceManager : public IMSurfaceManager, public IMStatus 
{ 
private:   
      SurfaceManager() ;  

      SurfaceManager(const SurfaceManager &module) ;
      
      SurfaceManager& operator = (const SurfaceManager &module) ;
public:
      virtual const char*  getClassName() const { return "SurfaceManager" ;}
      /**
      *   nType :  0 - 调用init函数
      **/ 
      static SmartPtr<SurfaceManager>& singleton() ;

	/**
	* 初始化模块内部参数，启动线程等
	*/
	virtual int init() ;

	/**
	* 退出模块内部线程，释放内存等
	*/
	virtual int exit() ;     

      virtual ~SurfaceManager() ;
      
     /**
	 * 此后为SurfaceManagerClient通用接口函数
	 */      
  
};

}  // namespace iris
#endif
