/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/20
**   File: SurfaceManagerClient.cpp
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#include "SurfaceManagerClient.h"

namespace iris
{

class SurfaceManagerClientAllocate {
public:
    static SurfaceManagerClient* allocate()  {
        return (new SurfaceManagerClient()) ;
    }
};

SurfaceManagerClient::SurfaceManagerClient()
{}
  
SurfaceManagerClient::~SurfaceManagerClient()
{} 

SmartPtr<SurfaceManagerClient> SurfaceManagerClient::allocate(int nType)
{
    SmartPtr<SurfaceManagerClient> module(SurfaceManagerClientAllocate::allocate()) ;
    if (nType == 0)
       module->init() ;
    return module ;
}

	/**
	* 初始化模块内部参数，启动线程等
	*/
int SurfaceManagerClient::init()
{
    int nCode = get(IMStatus::INIT) ;
    if (nCode != 0)
        return nCode ;   
    printf("SurfaceManagerClient::init()\n") ;
    
    set(IMStatus::RUN) ;
    return 0 ;
}

	/**
	* 退出模块内部线程，释放内存等
	*/
int SurfaceManagerClient::exit()
{
    int nCode = get(IMStatus::EXIT) ;
    if (nCode != 0)
        return nCode ;   
    printf("SurfaceManagerClient::exit()\n") ;
    set(IMStatus::NO) ;
    return 0 ;
}

/**
* 此后为SurfaceManagerClient通用接口函数
*/

}  // namespace iris


#if defined(__cplusplus)
extern "C" {
#endif

__attribute__((visibility("default"))) void*  allocateSurfaceManagerClient()
{
    return (void*) iris::SurfaceManagerClientAllocate::allocate();
}

#if defined(__cplusplus)
}
#endif