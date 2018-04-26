/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/20
**   File: SurfaceManagerClient.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_SURFACE_MANAGER_CLIENT_H
#define IMODULE_SURFACE_MANAGER_CLIENT_H


#include "IMSurfaceManagerClient.h"
#include "IStatus.h"

#include <memory>


namespace iris
{
class SurfaceManagerClient : public IMSurfaceManagerClient , public IMStatus
{
private:
      friend class SurfaceManagerClientAllocate ;   
      SurfaceManagerClient() ;  

      SurfaceManagerClient(const SurfaceManagerClient &module) ;
      
      SurfaceManagerClient& operator = (const SurfaceManagerClient &module) ;
public:
      /**
      *   nType :  0 - 调用init函数
      **/ 
      static SmartPtr<SurfaceManagerClient> allocate(int nType = 0) ;

      virtual ~SurfaceManagerClient() ;

      virtual const char*  getClassName() const { return "SurfaceManagerClient" ;}
	/**
	* 初始化模块内部参数，启动线程等
	*/
	virtual int init() ;

	/**
	* 退出模块内部线程，释放内存等
	*/
	virtual int exit() ;     
      
     /**
	 * 此后为SurfaceManagerClient通用接口函数
	 */      
  
};

}  // namespace iris
#endif
