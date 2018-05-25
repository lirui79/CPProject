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
#include "IMPropertyClient.h"
#include "Mutex.h"
#include <cstdlib>  
#include <dlfcn.h>
#include <stdarg.h>

namespace iris
{

Mutex& AllocateLock() {
    static Mutex mutex ;
    return mutex ;
}

class ModuleLoader : public virtual SmartObject {
public:
    typedef void* (*allocate_type)(...) ; 
private:
    friend class IMSurfaceManager ;
    friend class IMWindowManager ;
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

            std::map<std::string , allocate_type>::iterator it = mAllocates.find(szFName) ;
            if (it != mAllocates.end()) {
                printf("find %s\n" , szFName) ;
                return it->second ;
            }

            printf("not find %s\n" , szFName) ;
            allocate_type allocate ;
            if (mHandle == NULL)
                mHandle = dlopen(mName.c_str() , RTLD_NOW) ;
            if (mHandle == NULL)
                return NULL;
            allocate =  (allocate_type) dlsym(mHandle , szFName) ;
            if (allocate == NULL) 
                return NULL ;//            std::string fName = szFName ;
            mAllocates[szFName] = allocate ;
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
	std::map<std::string , SmartPtr<IModule> >        mModules ;
public:
    ModuleLoader() {
    }

    ~ModuleLoader() {
        ModuleManager::singleton()->exit() ;
        mModules.clear() ;
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
                printf("not find %s\n" , szLName) ;
            } else {
                loader = it->second ;
                printf("find %s\n" , szLName) ;
            }
        }

        allocate_type allocator = loader->get(szFName) ;
        if (allocator == NULL)
            return NULL ;
        return allocator() ;
    }

    template<typename T>
	void* allocate(const char* szLName , const char *szFName , T t) {
        if (szLName == NULL || szFName == NULL)
            return NULL  ;
        std::shared_ptr<Loader> loader ;
        {
            MutexLocker  locker(mLMutex) ;
            std::map<std::string , std::shared_ptr<Loader> >::iterator it = mLoaders.find(szLName) ;
            if (it == mLoaders.end()) {
                loader = std::shared_ptr<Loader>(new Loader(szLName)) ;
                mLoaders[szLName] = loader ;
                printf("not find %s\n" , szLName) ;
            } else {
                loader = it->second ;
                printf("find %s\n" , szLName) ;
            }
        }

        allocate_type allocator = loader->get(szFName) ;
        if (allocator == NULL)
            return NULL ;
        return allocator(t) ;
    }

    template<typename T , typename U>
	void* allocate(const char* szLName , const char *szFName , T t , U u) {
        if (szLName == NULL || szFName == NULL)
            return NULL  ;
        std::shared_ptr<Loader> loader ;
        {
            MutexLocker  locker(mLMutex) ;
            std::map<std::string , std::shared_ptr<Loader> >::iterator it = mLoaders.find(szLName) ;
            if (it == mLoaders.end()) {
                loader = std::shared_ptr<Loader>(new Loader(szLName)) ;
                mLoaders[szLName] = loader ;
                printf("not find %s\n" , szLName) ;
            } else {
                loader = it->second ;
                printf("find %s\n" , szLName) ;
            }
        }

        allocate_type allocator = loader->get(szFName) ;
        if (allocator == NULL)
            return NULL ;
        return allocator(t , u) ;
    }

    template<typename T , typename U , typename V>
	void* allocate(const char* szLName , const char *szFName , T t , U u , V v) {
        if (szLName == NULL || szFName == NULL)
            return NULL  ;
        std::shared_ptr<Loader> loader ;
        {
            MutexLocker  locker(mLMutex) ;
            std::map<std::string , std::shared_ptr<Loader> >::iterator it = mLoaders.find(szLName) ;
            if (it == mLoaders.end()) {
                loader = std::shared_ptr<Loader>(new Loader(szLName)) ;
                mLoaders[szLName] = loader ;
                printf("not find %s\n" , szLName) ;
            } else {
                loader = it->second ;
                printf("find %s\n" , szLName) ;
            }
        }

        allocate_type allocator = loader->get(szFName) ;
        if (allocator == NULL)
            return NULL ;
        return allocator(t , u , v) ;
    }

	allocate_type get(const char* szLName , const char *szFName) {
        if (szLName == NULL || szFName == NULL)
            return NULL  ;
        std::shared_ptr<Loader> loader ;
        {
            MutexLocker  locker(mLMutex) ;
            std::map<std::string , std::shared_ptr<Loader> >::iterator it = mLoaders.find(szLName) ;
            if (it == mLoaders.end()) {
                loader = std::shared_ptr<Loader>(new Loader(szLName)) ;
                mLoaders[szLName] = loader ;
                printf("not find %s\n" , szLName) ;
            } else {
                loader = it->second ;
                printf("find %s\n" , szLName) ;
            }
        }

        allocate_type allocator = loader->get(szFName) ;
        if (allocator == NULL)
            return NULL ;
        return allocator;
    }

    IModule*  get(const char* szMName , const char* szLName , const char *szFName) {
        if (szMName == NULL)
            return NULL ;
        MutexLocker  locker(AllocateLock()) ;
        std::map<std::string , SmartPtr<IModule> >::iterator it = mModules.find(szMName) ;
        if (it != mModules.end())
            return it->second.get();

        //allocate_type allocator = get(szLName , szFName) ;
        //SmartPtr<IModule> module = (IModule*) allocator(szLName , szFName) ;
        SmartPtr<IModule> module = (IModule*) allocate(szLName , szFName) ;
        mModules[szMName] = module;
        return module.get();
    }

    template<typename T>
    IModule*  get(const char* szMName , const char* szLName , const char *szFName , T t) {
        if (szMName == NULL)
            return NULL ;
        MutexLocker  locker(AllocateLock()) ;
        std::map<std::string , SmartPtr<IModule> >::iterator it = mModules.find(szMName) ;
        if (it != mModules.end())
            return it->second.get();
        SmartPtr<IModule> module = (IModule*) allocate(szLName , szFName , t) ;
        mModules[szMName] = module;
        return module.get();
    }

    template<typename T , typename U>
    IModule*  get(const char* szMName , const char* szLName , const char *szFName , T t , U u) {
        if (szMName == NULL)
            return NULL ;
        MutexLocker  locker(AllocateLock()) ;
        std::map<std::string , SmartPtr<IModule> >::iterator it = mModules.find(szMName) ;
        if (it != mModules.end())
            return it->second.get();
        SmartPtr<IModule> module = (IModule*) allocate(szLName , szFName , t , u) ;
        mModules[szMName] = module;
        return module.get();
    }

    template<typename T , typename U , typename V>
    IModule*  get(const char* szMName , const char* szLName , const char *szFName , T t , U u , V v) {
        if (szMName == NULL)
            return NULL ;
        MutexLocker  locker(AllocateLock()) ;
        std::map<std::string , SmartPtr<IModule> >::iterator it = mModules.find(szMName) ;
        if (it != mModules.end())
            return it->second.get();
        SmartPtr<IModule> module = (IModule*) allocate(szLName , szFName , t , u , v) ;
        mModules[szMName] = module;
        return module.get();
    }

    virtual const char*  getClassName() const { return "ModuleLoader" ;}  

    static SmartPtr<ModuleLoader>& singleton() {
        static Mutex mutex ;
        static SmartPtr<ModuleLoader> singleton ;
        printf("ModuleLoader::singleton()\n") ;
        if (singleton != NULL)
            return singleton ;
        MutexLocker  locker(mutex) ;
        if (singleton == NULL)
        singleton = new ModuleLoader() ;
        printf("ModuleLoader::singleton() new\n") ;
        return singleton ;
    }
} ;

SmartPtr<IMSurfaceManager> IMSurfaceManager::singleton()
{
/*    static SmartPtr<IMSurfaceManager> module ;
    if (module != NULL)
        return module ;
    MutexLocker  locker(AllocateLock()) ;
    if (module != NULL)
        return module ;   
    int *ptr = (int*) ModuleLoader::singleton()->allocate("libSurfaceManager.so" , "allocateINT") ;
    printf("allocateINT  %p \n" , ptr) ;
    delete []ptr ;

    module = (IMSurfaceManager*) ModuleLoader::singleton()->allocate("libSurfaceManager.so" , "allocateSurfaceManager") ;

    ptr = (int*) ModuleLoader::singleton()->allocate("libSurfaceManager.so" , "allocateINT") ;
    printf("allocateINT  %p \n" , ptr) ;
    delete []ptr ;
    return module ; */
    typedef int* (*allocate_type)() ;
    allocate_type allocate = (allocate_type) ModuleManager::singleton()->get("libSurfaceManager.so" , "allocateINT") ;
    int *ptr = allocate() ;
    printf("allocateINT  %p \n" , ptr) ;
    delete []ptr ;

    ptr = (int*)ModuleManager::singleton()->allocate("libSurfaceManager.so" , "allocateInt", 1) ;

    printf("allocateInt %d\n" , *ptr) ;
    delete ptr ;

    SmartPtr<IMSurfaceManager> module = dynamic_cast<IMSurfaceManager*>(ModuleManager::singleton()->get("IMSurfaceManager" , "libSurfaceManager.so" , "allocateSurfaceManager")) ;

    ptr = (int*) ModuleManager::singleton()->allocate("libSurfaceManager.so" , "allocateINT") ;
    printf("allocateINT  %p \n" , ptr) ;
    delete []ptr ;

    return module ;
}


SmartPtr<IMPropertyClient> IMPropertyClient::singleton()
{
    typedef void* (*allocate_type)() ;
    SmartPtr<IMPropertyClient> module = dynamic_cast<IMPropertyClient*>(ModuleManager::singleton()->get("IMPropertyClient" , "libPropertyClient.so" , "allocatePropertyClient")) ;
    return module ;
}



SmartPtr<IMWindowManager> IMWindowManager::singleton()
{
/*
    static SmartPtr<IMWindowManager> module ;
    if (module != NULL)
        return module ;
    MutexLocker  locker(AllocateLock()) ;
    if (module != NULL)
        return module ;
    module = (IMWindowManager*) ModuleLoader::singleton()->allocate("libWindowManager.so" , "allocateWindowManager") ;
    */
    typedef void* (*allocate_type)(const char *s , int n) ;
    allocate_type allocator = (allocate_type) ModuleManager::singleton()->get("libWindowManager.so" , "allocateTest") ;
    void *test = allocator("hello" , 1) ;
    printf("test %p\n" , test) ;
    delete test ;

    test = ModuleManager::singleton()->allocate("libWindowManager.so" , "allocateTest" , "world" , 10000) ;
    printf("test %p\n" , test) ;
    delete test ;

    SmartPtr<IMWindowManager> module = dynamic_cast<IMWindowManager*>(ModuleManager::singleton()->get("IMWindowManager" , "libWindowManager.so" , "allocateWindowManager")) ;
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
    typedef IMSurfaceManagerClient* (*allocate_type)() ;
    allocate_type allocator = (allocate_type) ModuleManager::singleton()->get("libSurfaceManagerClient.so", "allocateSurfaceManagerClient") ;
    IMSurfaceManagerClient* sm = allocator() ;
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
ModuleManager::Loader::Loader(const char *szLName) : mName(szLName) , mHandle(NULL) {
}

ModuleManager::Loader::~Loader()  {
    if (mHandle != NULL)
        dlclose(mHandle) ;
    mHandle = NULL ;
    mAllocates.clear() ;
}

ModuleManager::allocate_type ModuleManager::Loader::get(const char *szFName)  {
    if (szFName == NULL)
        return NULL ;

    std::map<std::string , allocate_type>::iterator it = mAllocates.find(szFName) ;
    if (it != mAllocates.end()) {
        printf("find %s\n" , szFName) ;
        return it->second ;
    }

    printf("not find %s\n" , szFName) ;
    allocate_type allocate ;
    if (mHandle == NULL)
        mHandle = dlopen(mName.c_str() , RTLD_NOW) ;
    if (mHandle == NULL)
        return NULL;
    allocate =  (allocate_type) dlsym(mHandle , szFName) ;
    if (allocate == NULL) 
        return NULL ;//            std::string fName = szFName ;
    mAllocates[szFName] = allocate ;
    return allocate ;
}

const char*   ModuleManager::Loader::get() const {
        return mName.c_str() ;
}

ModuleManager::ModuleManager()
{}

ModuleManager::~ModuleManager()
{
    mModules.clear() ;
    mLoaders.clear() ;   
}

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
    int nCode = IMStatus::get(IMStatus::INIT) ;
    if (nCode != 0)
        return nCode ;   

    printf("ModuleManager::init()\n") ;
    //mModules.push_back(IMSurfaceManager::singleton()) ;
    IMSurfaceManager::singleton()->init() ;

    //mModules.push_back(IMWindowManager::singleton()) ;
    IMWindowManager::singleton()->init() ;

    printf("ModuleManager::init()  push IMWindowManager\n") ;
    /**
    *   check IMSurfaceManager module start 
    **/
    
    IMStatus::set(IMStatus::RUN) ;
    return 0 ;
}

/**
* 退出模块内部线程，释放内存等
*/
int ModuleManager::exit()
{
    int nCode = IMStatus::get(IMStatus::EXIT) ;
    if (nCode != 0)
        return nCode ;   
    //printf("ModuleManager::exit()\n") ;
    /*std::list<SmartPtr<IModule> >::iterator it ;
    for (it = mModules.begin() ; it != mModules.end() ; ++it)
       (*it)->exit() ;*/
    //printf("ModuleManager::exit()  mModules  exit\n") ;
    /**
    *   check IMSurfaceManager module exit 
    **/
    mWindowManager.reset(NULL) ;
    mModules.clear() ;
    IMStatus::set(IMStatus::NO) ;
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

    mWindowManager = (IMWindowManager*) get("IMWindowManager" , "libWindowManager.so" , "allocateWindowManager") ;
    return mWindowManager ;   
}

void* ModuleManager::allocate(const char* szLName , const char *szFName) {
    if (szLName == NULL || szFName == NULL)
        return NULL  ;
    std::shared_ptr<Loader> loader ;
    {
        MutexLocker  locker(mLMutex) ;
        std::map<std::string , std::shared_ptr<Loader> >::iterator it = mLoaders.find(szLName) ;
        if (it == mLoaders.end()) {
            loader = std::shared_ptr<Loader>(new Loader(szLName)) ;
            mLoaders[szLName] = loader ;
            printf("not find %s\n" , szLName) ;
        } else {
            loader = it->second ;
            printf("find %s\n" , szLName) ;
        }
    }

    allocate_type allocator = loader->get(szFName) ;
    if (allocator == NULL)
        return NULL ;
    return allocator() ;
}

template<typename T>
void* ModuleManager::allocate(const char* szLName , const char *szFName , T t) {
    if (szLName == NULL || szFName == NULL)
        return NULL  ;
    std::shared_ptr<Loader> loader ;
    {
        MutexLocker  locker(mLMutex) ;
        std::map<std::string , std::shared_ptr<Loader> >::iterator it = mLoaders.find(szLName) ;
        if (it == mLoaders.end()) {
            loader = std::shared_ptr<Loader>(new Loader(szLName)) ;
            mLoaders[szLName] = loader ;
            printf("not find %s\n" , szLName) ;
        } else {
            loader = it->second ;
            printf("find %s\n" , szLName) ;
        }
    }

    allocate_type allocator = loader->get(szFName) ;
    if (allocator == NULL)
        return NULL ;
    return allocator(t) ;
}

template<typename T , typename U>
void* ModuleManager::allocate(const char* szLName , const char *szFName , T t , U u) {
    if (szLName == NULL || szFName == NULL)
        return NULL  ;
    std::shared_ptr<Loader> loader ;
    {
        MutexLocker  locker(mLMutex) ;
        std::map<std::string , std::shared_ptr<Loader> >::iterator it = mLoaders.find(szLName) ;
        if (it == mLoaders.end()) {
            loader = std::shared_ptr<Loader>(new Loader(szLName)) ;
            mLoaders[szLName] = loader ;
            printf("not find %s\n" , szLName) ;
        } else {
            loader = it->second ;
            printf("find %s\n" , szLName) ;
        }
    }

    allocate_type allocator = loader->get(szFName) ;
    if (allocator == NULL)
        return NULL ;
    return allocator(t , u) ;
}

template<typename T , typename U , typename V>
void* ModuleManager::allocate(const char* szLName , const char *szFName , T t , U u , V v) {
    if (szLName == NULL || szFName == NULL)
        return NULL  ;
    std::shared_ptr<Loader> loader ;
    {
        MutexLocker  locker(mLMutex) ;
        std::map<std::string , std::shared_ptr<Loader> >::iterator it = mLoaders.find(szLName) ;
        if (it == mLoaders.end()) {
            loader = std::shared_ptr<Loader>(new Loader(szLName)) ;
            mLoaders[szLName] = loader ;
            printf("not find %s\n" , szLName) ;
        } else {
            loader = it->second ;
            printf("find %s\n" , szLName) ;
        }
    }

    allocate_type allocator = loader->get(szFName) ;
    if (allocator == NULL)
        return NULL ;
    return allocator(t , u , v) ;
}

ModuleManager::allocate_type ModuleManager::get(const char* szLName , const char *szFName) {
    if (szLName == NULL || szFName == NULL)
        return NULL  ;
    std::shared_ptr<Loader> loader ;
    {
        MutexLocker  locker(mLMutex) ;
        std::map<std::string , std::shared_ptr<Loader> >::iterator it = mLoaders.find(szLName) ;
        if (it == mLoaders.end()) {
            loader = std::shared_ptr<Loader>(new Loader(szLName)) ;
            mLoaders[szLName] = loader ;
            printf("not find %s\n" , szLName) ;
        } else {
            loader = it->second ;
            printf("find %s\n" , szLName) ;
        }
    }

    allocate_type allocator = loader->get(szFName) ;
    if (allocator == NULL)
        return NULL ;
    return allocator;
}

IModule*  ModuleManager::get(const char* szMName , const char* szLName , const char *szFName) {
    if (szMName == NULL)
        return NULL ;
    MutexLocker  locker(AllocateLock()) ;
    std::map<std::string , SmartPtr<IModule> >::iterator it = mModules.find(szMName) ;
    if (it != mModules.end())
        return it->second.get();

    //allocate_type allocator = get(szLName , szFName) ;
    //SmartPtr<IModule> module = (IModule*) allocator(szLName , szFName) ;
    SmartPtr<IModule> module = (IModule*) allocate(szLName , szFName) ;
    mModules[szMName] = module;
    return module.get();
}

template<typename T>
IModule*  ModuleManager::get(const char* szMName , const char* szLName , const char *szFName , T t) {
    if (szMName == NULL)
        return NULL ;
    MutexLocker  locker(AllocateLock()) ;
    std::map<std::string , SmartPtr<IModule> >::iterator it = mModules.find(szMName) ;
    if (it != mModules.end())
        return it->second.get();
    SmartPtr<IModule> module = (IModule*) allocate(szLName , szFName , t) ;
    mModules[szMName] = module;
    return module.get();
}

template<typename T , typename U>
IModule*  ModuleManager::get(const char* szMName , const char* szLName , const char *szFName , T t , U u) {
    if (szMName == NULL)
        return NULL ;
    MutexLocker  locker(AllocateLock()) ;
    std::map<std::string , SmartPtr<IModule> >::iterator it = mModules.find(szMName) ;
    if (it != mModules.end())
        return it->second.get();
    SmartPtr<IModule> module = (IModule*) allocate(szLName , szFName , t , u) ;
    mModules[szMName] = module;
    return module.get();
}

template<typename T , typename U , typename V>
IModule*  ModuleManager::get(const char* szMName , const char* szLName , const char *szFName , T t , U u , V v) {
    if (szMName == NULL)
        return NULL ;
    MutexLocker  locker(AllocateLock()) ;
    std::map<std::string , SmartPtr<IModule> >::iterator it = mModules.find(szMName) ;
    if (it != mModules.end())
        return it->second.get();
    SmartPtr<IModule> module = (IModule*) allocate(szLName , szFName , t , u , v) ;
    mModules[szMName] = module;
    return module.get();
}


}  // namespace iris
