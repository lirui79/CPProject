/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/04/13
**   File: Log.cpp
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#include "Log.h"
#include <stdarg.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/file.h>

namespace iris
{

    SmartPtr<ILog> ILog::singleton() {
        return Log::singleton() ;
    }

    Log::item::item() {}

    Log::item::~item() {}

    Log::Log() {        
    }

    Log::~Log() {
    }
      
    SmartPtr<Log>& Log::singleton() {
        static Mutex mutex ;
        static SmartPtr<Log> singleton ;
        printf("Log::singleton()\n") ;
        if (singleton != NULL)
            return singleton ;
        MutexLocker  locker(mutex) ;
        if (singleton == NULL) 
           singleton = new Log() ;
        printf("Log::singleton() new\n") ;
        return singleton ;
    }
  
	/**
	 * 初始化模块内部参数，启动线程等
	 */
	int Log::init(const char *folder) {
        int nCode = get(IMStatus::INIT) ;
        printf("Log::init code %d\n" , nCode) ;
        if (nCode != 0)
            return nCode ;        
        strncpy(mFolder  , folder, 63);
        sprintf(strrchr(mFolder , '/') + 1  , "log") ;
        if (access(mFolder , F_OK) == -1)
           mkdir(mFolder , S_IRWXU) ;

        sprintf(mFileName , "%s/log.log" , mFolder ) ;

        {
            IDelegate0<Log> *pIDelegate0 = new IDelegate0<Log>(this , &Log::run) ;
            MutexLocker locker(mLMutex) ;
            mThread = new Thread() ;
            mThread->Start(pIDelegate0) ;	
        }

        set(IMStatus::RUN) ;
        return 0 ;
    }

	/**
	 * 退出模块内部线程，释放内存等
	 */
	int Log::exit() {
        int nCode = get(IMStatus::EXIT) ;
        if (nCode != 0)
            return nCode ;
        printf("Log::run signal exit\n") ;
        {
            MutexLocker locker(mLMutex) ;
            mLEvent.SignalOne() ; 
        }

        printf("Log::run wait exit\n") ;
        {
            MutexLocker locker(mEMutex) ;
            mEEvent.Wait(mEMutex , 5000) ; 
        }
        
        set(IMStatus::NO) ;
        return 0 ;   
    }

	/**
	 * 退出模块内部线程，释放内存等
	 */
	int Log::write(const char* module , int levelid , const char *format , ...) {
        int nCode = get(IMStatus::RUN) ;
        printf("Log::write code %d\n" , nCode) ;
        if (nCode != 0)
            return nCode ;
        const char *szlevel[] = {"Trace" , "Debug" , "Info" , "Warn" , "Error" , "Fatal"} ;
        time_t nowtime = time(0);
        size_t  pos ;
        va_list args ;
        item* im = new item() ;
        pos  = strftime(im->mStrLog , 32 , "%F %X " , localtime(&nowtime) );
        if (levelid > 5 )
              levelid = 5 ;
        pos +=sprintf(im->mStrLog + pos , "%s %s " , module , szlevel[levelid]);

        va_start(args , format) ; // The last argument to wvsprintf points to the arguments
        pos += vsnprintf(im->mStrLog + pos , 1024 - pos , format , args); 	//   _vsntprintf (szBuf , sizeof (szBuf) , format , pArgList) ;
        va_end(args) ;
        im->mStrLog[pos] = '\0' ;
        {
            MutexLocker locker(mLMutex) ;
            mLogs.push_back(im) ;
            mLEvent.SignalOne() ; 
        }
        return 0 ;
    }
    
    int Log::writelog() {
        std::list<item*> Logs ;
        {
            MutexLocker locker(mLMutex) ;
            Logs = mLogs ;
            mLogs.clear() ;
        }

        if (Logs.empty())
            return 0 ;

        FILE *fp = fopen(mFileName , "a") ;
        flock(fp->_fileno , LOCK_EX) ;
        for (std::list<item*>::iterator it = Logs.begin() ; it != Logs.end() ; ++it) {
            item *im = *it ;
            fprintf(fp , "%s\n" , im->mStrLog);
            delete im ;
        }
        fclose(fp) ;

        struct  stat   statlog ;
        if (stat(mFileName , &statlog) >= 0)
        {
             if (statlog.st_size >= (5 * 1024 * 1024))
             {
                char szFileNew[256] , szNowTime[64];
                time_t  nowtime = time(0) ;
                strftime(szNowTime , 64 , "%F %X " , localtime(&nowtime) );
                sprintf(szFileNew , "%s/%s.log" , mFolder , szNowTime) ;
                rename(mFileName , szFileNew) ;
             }
        }

        flock(fp->_fileno , LOCK_UN) ;
        return 0 ;
    }

    int Log::run() {

        while(work() == 0) {
            writelog() ;
            MutexLocker locker(mLMutex) ;
            if(mLogs.empty()) {
               mLEvent.Wait(mLMutex , 5000) ; 
            }            
        }
        writelog() ;

        printf("Log::run will exit\n") ;
        {
            MutexLocker locker(mEMutex) ;
            mEEvent.SignalOne() ; 
        }
        printf("Log::run exit\n") ;
        return 0 ;
    }

}