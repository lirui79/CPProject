/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/20
**   File: ModuleManager.cpp
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#include "IMSurfaceManager.h"
#include "ModuleManager.h"
#include "IMSurfaceManagerClient.h"
#include "Mutex.h"
#include <cstdlib>  
#include <dlfcn.h>  

namespace iris
{

Mutex& AllocateLock() {
    static Mutex mutex ;
    return mutex ;
}

class ModuleLoader {
private:
    typedef void* (*allocate_type)() ; 
    class Loader {
		public:
        Loader(const char *szLName) : mName(szLName) , mHandle(NULL) {}
        ~Loader()  {
            if (mHandle != NULL)
            dlclose(mHandle) ;
            mHandle = NULL ;
            mAllocates.clear() ;
        }

        allocate_type get(const char *szFName)  {
            if (szFName == NULL)
                return NULL ;
            
            std::string fName = szFName ;
            std::map<std::string , allocate_type>::iterator it = mAllocates.find(fName) ;
            if (it != mAllocates.end())
                return it->second ;

            allocate_type allocate ;
            if (mHandle == NULL)
                mHandle = dlopen(mName.c_str() , RTLD_NOW) ;
            if (mHandle == NULL)
                return NULL;
            allocate =  (allocate_type) dlsym(mHandle , szFName) ;
            if (allocate == NULL) 
                return NULL ;
            mAllocates[fName] = allocate ;
            return allocate ;
        }

        const char*   get() const {
                return mName.c_str() ;
        }

        private:
		  std::string mName ; // so  name
		  void*       mHandle ; // so handle
		  std::map<std::string , allocate_type> mAllocates ; // name -> function
	} ;

	Mutex                           mLMutex ;
	std::map<std::string , std::shared_ptr<Loader> >  mLoaders ;
public:
    ModuleLoader() {
    }

    ~ModuleLoader() {
        mLoaders.clear() ;        
    }

	void* allocate(const char* szLName , const char *szFName) {
        if (szLName == NULL || szFName == NULL)
            return NULL  ;
        std::shared_ptr<Loader> loader ;
        {
            MutexLocker  locker(mLMutex) ;
            std::map<std::string , std::shared_ptr<Loader> >::iterator it = mLoaders.find(szLName) ;
            if (it == mLoaders.end()) {
                loader = std::shared_ptr<Loader>(new Loader(szLName)) ;
                mLoaders[szLName] = loader ;
            } else {
                loader = it->second ;
            }
        }

        allocate_type allocate = loader->get(szFName) ;
        if (allocate == NULL)
            return NULL ;
        return allocate() ;
    }  
} ;

static ModuleLoader mLoader ;

SmartPtr<IMSurfaceManager>& IMSurfaceManager::singleton()
{
    static SmartPtr<IMSurfaceManager> module ;
    if (module != NULL)
        return module ;
    MutexLocker  locker(AllocateLock()) ;
    if (module != NULL)
        return module ;
    module = (IMSurfaceManager*) mLoader.allocate("libSurfaceManager.so" , "allocateSurfaceManager") ;
    return module ;  
}

SmartPtr<IMWindowManager>& IMWindowManager::singleton()
{
    static SmartPtr<IMWindowManager> module ;
    if (module != NULL)
        return module ;
    MutexLocker  locker(AllocateLock()) ;
    if (module != NULL)
        return module ;
    module = (IMWindowManager*) mLoader.allocate("libWindowManager.so" , "allocateWindowManager") ;
    return module ;    
}

SmartPtr<IMSurfaceManagerClient> IMSurfaceManagerClient::allocate(int nType)
{
/*    void *handle ;
    typedef void* (*fun_type)() ;
    handle = dlopen("libSurfaceManagerClient.so" , RTLD_NOW) ;
    fun_type fun = (fun_type) dlsym(handle , "allocateSurfaceManagerClient") ;
    SmartPtr<IMSurfaceManagerClient>module((IMSurfaceManagerClient*)fun()) ;
    if (nType == 0)
       module->init() ;
    return module ; */
    void* sm = mLoader.allocate("libSurfaceManagerClient.so", "allocateSurfaceManagerClient") ;
    printf("IMSurfaceManagerClient::allocate %p \n" , sm) ;
    SmartPtr<IMSurfaceManagerClient> module((IMSurfaceManagerClient*)sm) ;
    if (nType == 0)
       module->init() ;
    return module ;
}

IMModuleManager::IMModuleManager()
{}

IMModuleManager::~IMModuleManager()
{}

SmartPtr<IMModuleManager> IMModuleManager::singleton()
{
    return ModuleManager::singleton() ;
}

/*
**
*/
ModuleManager::ModuleManager()
{}

ModuleManager::~ModuleManager()
{}

SmartPtr<ModuleManager>& ModuleManager::singleton()
{
    static SmartPtr<ModuleManager> singleton ;
    printf("ModuleManager::singleton()\n") ;
    if (singleton != NULL)
        return singleton ;
    MutexLocker  locker(AllocateLock()) ;
    if (singleton == NULL)
       singleton = new ModuleManager() ;
    printf("ModuleManager::singleton() new\n") ;
    return singleton ;
}

/**
* 初始化模块内部参数，启动线程等
*/
int ModuleManager::init()
{
    int nCode = get(IMStatus::INIT) ;
    if (nCode != 0)
        return nCode ;   

    printf("ModuleManager::init()\n") ;
    mModules.push_back(IMSurfaceManager::singleton()) ;
    IMSurfaceManager::singleton()->init() ;

    mModules.push_back(IMWindowManager::singleton()) ;
    IMWindowManager::singleton()->init() ;

    printf("ModuleManager::init()  push IMWindowManager\n") ;
    /**
    *   check IMSurfaceManager module start 
    **/
    
    set(IMStatus::RUN) ;
    return 0 ;
}

/**
* 退出模块内部线程，释放内存等
*/
int ModuleManager::exit()
{
    int nCode = get(IMStatus::EXIT) ;
    if (nCode != 0)
        return nCode ;   
    printf("ModuleManager::exit()\n") ;
    std::list<SmartPtr<IModule> >::iterator it ;
    for (it = mModules.begin() ; it != mModules.end() ; ++it)
       (*it)->exit() ;
    printf("ModuleManager::exit()  mModules  exit\n") ;
    /**
    *   check IMSurfaceManager module exit 
    **/
    
    mModules.clear() ;
    set(IMStatus::NO) ;
    return 0 ;
}


SmartPtr<IMWindowManager>&  ModuleManager::getWindowManager()
{
/*    int nCode = isCanRun() ;
    if (nCode != 0)
       return mWindowManager ;*/
/*    void *handle ;
    typedef void* (*fun_type)() ;
    if (mWindowManager != NULL)
        return mWindowManager ;
    handle = dlopen("libWindowManager.so" , RTLD_NOW) ;
    fun_type fun = (fun_type) dlsym(handle , "allocateWindowManager") ;
    mWindowManager = (IMWindowManager*)fun() ;
    return mWindowManager ;*/
    if (mWindowManager != NULL)
        return mWindowManager ;
    MutexLocker  locker(AllocateLock()) ;
    if (mWindowManager != NULL)
        return mWindowManager ;
    mWindowManager = (IMWindowManager*) mLoader.allocate("libWindowManager.so" , "allocateWindowManager") ;
    return mWindowManager ;   
}


}  // namespace iris
