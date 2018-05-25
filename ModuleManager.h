/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/20
**   File: ModuleManager.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IMODULE_MODULE_MANAGER_H
#define IMODULE_MODULE_MANAGER_H

#include "IMModuleManager.h"
#include "IMWindowManager.h"
#include "IStatus.h"

#include <list>
#include <memory>
#include <map>

namespace iris
{
class ModuleManager : public IMModuleManager , public IMStatus {
public:
    typedef void* (*allocate_type)(...) ; 
private:
    friend class IMSurfaceManager ;
    friend class IMWindowManager ;
    friend class IMPropertyClient ;
    class Loader {
		public:
        Loader(const char *szLName);
        ~Loader();

        allocate_type get(const char *szFName);

        const char*   get() const ;

        private:
		  std::string mName ; // so  name
		  void*       mHandle ; // so handle
		  std::map<std::string , allocate_type> mAllocates ; // name -> function
	} ;
private:
	Mutex                           mLMutex ;
	std::map<std::string , std::shared_ptr<Loader> >  mLoaders ;
	std::map<std::string , SmartPtr<IModule> >        mModules ;
	SmartPtr<IMWindowManager>                         mWindowManager ;
private:
	ModuleManager() ;

	ModuleManager(const ModuleManager &module) ;

	ModuleManager& operator = (const ModuleManager &module) ;
      
public:
      
	static SmartPtr<ModuleManager>& singleton() ;

	virtual ~ModuleManager() ;

    virtual const char*  getClassName() const { return "ModuleManager" ;}    
	/**
	* 初始化模块内部参数，启动线程等
	*/
	virtual int init() ;

	/**
	* 退出模块内部线程，释放内存等
	*/
	virtual int exit() ;

	SmartPtr<IMWindowManager>&  getWindowManager() ;

	virtual void* allocate(const char* szLName , const char *szFName);

	template<typename T>
	void* allocate(const char* szLName , const char *szFName , T t);

	template<typename T , typename U>
	void* allocate(const char* szLName , const char *szFName , T t , U u);

	template<typename T , typename U , typename V>
	void* allocate(const char* szLName , const char *szFName , T t , U u , V v);

	virtual allocate_type get(const char* szLName , const char *szFName) ;

private:
	virtual IModule*  get(const char* szMName , const char* szLName , const char *szFName);

	template<typename T>
	IModule*  get(const char* szMName , const char* szLName , const char *szFName , T t);

	template<typename T , typename U>
	IModule*  get(const char* szMName , const char* szLName , const char *szFName , T t , U u);

	template<typename T , typename U , typename V>
	IModule*  get(const char* szMName , const char* szLName , const char *szFName , T t , U u , V v);
};

}  // namespace iris
#endif
