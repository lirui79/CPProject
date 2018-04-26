/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/27
**   File: IMSurfaceManagerClient.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_IM_SURFACE_MANAGER_CLIENT_H
#define IMODULE_IM_SURFACE_MANAGER_CLIENT_H


#include "IModule.h"

#include <memory>


namespace iris
{
class IMSurfaceManagerClient : public virtual IModule
{
protected:
      IMSurfaceManagerClient() {}
private:      
      IMSurfaceManagerClient(const IMSurfaceManagerClient &module) ;
      
      IMSurfaceManagerClient& operator = (const IMSurfaceManagerClient &module) ;
public:   
      /**
      *   nType :  0 - 模块调用init函数
      **/   
      static SmartPtr<IMSurfaceManagerClient> allocate(int nType = 0) ;

      virtual ~IMSurfaceManagerClient() {}
	/**
	 * 初始化模块内部参数，启动线程等
	 */
	virtual int init()=0;
      virtual const char*  getClassName() const { return "IMSurfaceManagerClient" ;}    
     /**
	 * 此后为SurfaceManagerClient通用接口函数
	 */
      
};

}  // namespace iris
#endif
