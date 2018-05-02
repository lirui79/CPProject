/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/28
**   File: SurfaceManager.cpp
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/




#include "SurfaceManager.h"
#include "Mutex.h"

namespace iris
{

SurfaceManager::SurfaceManager()
{}
  
SurfaceManager::~SurfaceManager()
{}    
   
SmartPtr<SurfaceManager>& SurfaceManager::singleton()
{   
    static Mutex mutex ;
    static SmartPtr<SurfaceManager> singleton ;
    if (singleton != NULL)
        return singleton ;
    MutexLocker  locker(mutex) ;
    if (singleton == NULL)
       singleton = new SurfaceManager() ;
    return singleton ;
}

	/**
	* 初始化模块内部参数，启动线程等
	*/
int SurfaceManager::init()
{
    int nCode = get(IMStatus::INIT) ;
    if (nCode != 0)
        return nCode ;   
    printf("SurfaceManager::init()\n") ;
    
    set(IMStatus::RUN) ;
    return 0 ;
}

	/**
	* 退出模块内部线程，释放内存等
	*/
int SurfaceManager::exit()
{
    int nCode = get(IMStatus::EXIT) ;
    if (nCode != 0)
        return nCode ;   
    printf("SurfaceManager::exit()\n") ;
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

__attribute__((visibility("default"))) void*  allocateSurfaceManager()
{
    return (void*) iris::SurfaceManager::singleton().get();
}

#if defined(__cplusplus)
}
#endif