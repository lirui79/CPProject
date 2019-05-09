/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/28
**   File: WindowManager.cpp
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/




#include "WindowManager.h"
#include "Mutex.h"


namespace iris
{

WindowManager::WindowManager()
{}
  
WindowManager::~WindowManager()
{}    
   
SmartPtr<WindowManager>& WindowManager::singleton()
{
    static Mutex mutex ;
    static SmartPtr<WindowManager> singleton ;
    printf("WindowManager::singleton()\n") ;
    if (singleton != NULL)
        return singleton ;
    MutexLocker  locker(mutex) ;
    if (singleton == NULL)
       singleton = new WindowManager() ;
    printf("WindowManager::singleton() new\n") ;
    return singleton ;
}

	/**
	* 初始化模块内部参数，启动线程等
	*/
int WindowManager::init()
{
    int nCode = get(IMStatus::INIT) ;
    if (nCode != 0)
        return nCode ;   
    printf("WindowManager::init()\n") ;
    
    set(IMStatus::RUN) ;
    return 0 ;
}

	/**
	* 退出模块内部线程，释放内存等
	*/
int WindowManager::exit()
{
    int nCode = get(IMStatus::EXIT) ;
    if (nCode != 0)
        return nCode ;   
    printf("WindowManager::exit()\n") ;
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

__attribute__((visibility("default"))) void*  allocateWindowManager()
{
    return (void*) iris::WindowManager::singleton().get();
}

class test {
    public:
    test(int n , const char* s) : m(n) , str(s) {
        printf("n %d s %s\n" , n , s) ;
    }

    ~test() {}

    int m ;
    std::string str ;
};

__attribute__((visibility("default"))) void*  allocateTest(const char* s ,  int n)
{        
    printf("n %d s %s\n" , n , s) ;
    return (void*) (new test(n , s));
}


#if defined(__cplusplus)
}
#endif