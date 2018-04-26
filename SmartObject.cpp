/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/29
**   File: SmartObject.cpp
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#include "SmartObject.h"
#include "Mutex.h"
#include <stdarg.h>
#include <signal.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

namespace iris
{
    SmartObject::SmartObject() : mRefCount(0) {
    }

    SmartObject::~SmartObject() {
    }

    int  SmartObject::RefCount(int type) {
        static Mutex mutex ;
        if (type == 0){
            int nRefCount = 0 ;
            mutex.Lock() ;
            nRefCount = --mRefCount ;
            mutex.Unlock() ;
            print_log("class sub:%s %d\n" , getClassName() , nRefCount);
            if (nRefCount != 0)
                return nRefCount ;
            print_log("class delete:%s %d\n" , getClassName() , nRefCount);
            delete this ;
            return nRefCount ;
        } 

        if (type == 1){
            mutex.Lock() ;
            ++mRefCount ;
            mutex.Unlock() ;
        }

        print_log("class add:%s %d\n" , getClassName() , mRefCount);
        return mRefCount ;
    }

    const char*  SmartObject::getClassName() const{
        return "SmartObject" ;
    }

void print_log(const char *format , ...) {
    char szLog[1024];
    va_list args ;
    time_t  nowtime = time(0) ;
    size_t index = strftime(szLog , 64 , "%F %X " , localtime(&nowtime));
        
    va_start(args , format) ; // The last argument to wvsprintf points to the arguments
    index += vsnprintf(szLog + index , 1024 - index , format , args); 	//   _vsntprintf (szBuf , sizeof (szBuf) , format , pArgList) ;
    va_end(args) ;
    printf("%s\n" , szLog) ;
}

}