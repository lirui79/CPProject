#include "IMModuleManager.h"
#include "IMSurfaceManager.h"
#include "IMSurfaceManagerClient.h"
#include "Mutex.h"
#include "Thread.h"
#include "ILog.h"
#include <unistd.h>
#include <list>

using namespace iris ;
class testParam1 {
public :
    void f() {
        print_log("testParam1 f()\n") ;
    }

    void g() {
        print_log("testParam1 g()\n") ;
    }
} ;

class testParam2 {
public :
    void f() {
        printf("testParam2 f()\n") ;
    }

    void g() {
        print_log("testParam2 g()\n") ;
    }
} ;


class testThread ;
class testParam3 {
public :
    void f() {
        print_log("testParam3 f()\n") ;
    }

    void g() {
        print_log("testParam3 g()\n") ;
    }

    void t(testThread *thr) ;
} ;

class testThread : public virtual SmartObject {
    testParam1 tp ;
    testParam3 tp3 ;
public :
    
    int Start() {
        {
            IDelegate0<testThread> *pIDelegate0 = new IDelegate0<testThread>(this , &testThread::Run) ;
            SmartPtr<Thread> t(new Thread()) ;
            threads.push_back(t) ;
            t->Start(pIDelegate0) ;	
        }

        {
            IDelegate1<testThread , testParam1&> *pIDelegate1 = new IDelegate1<testThread ,testParam1&>(this , &testThread::Run , tp) ;
            SmartPtr<Thread> t(new Thread(pIDelegate1)) ;
            threads.push_back(t) ;
            //t->Start(pIDelegate1) ;	
        }


        {
            IDelegate3<testThread , testParam1& , testParam2* , testParam3> *pIDelegate3 = new IDelegate3<testThread , testParam1& , testParam2* , testParam3>(this , &testThread::Run , tp , new testParam2() , tp3) ;
            SmartPtr<Thread> t(new Thread()) ;
            threads.push_back(t) ;
            t->Start(pIDelegate3) ;	
        }

        IMModuleManager::singleton()->init() ;
        return 1 ;
    }

    int Run() {
        int nCount = 0 ;
        IMModuleManager::singleton()->init() ;
        while(nCount++ < 4) {

           print_log("testThread Run() count %d\n",nCount ) ;
           {
               print_log("thread %d time1 %ld \n" , pthread_self() , time(NULL)) ;
               mutex.Lock() ;
               event.Wait(mutex , 1000) ;
               mutex.Unlock() ;
               print_log("thread %d time2 %ld \n" , pthread_self() , time(NULL)) ;
           }
           tp.g() ;
        }

        return 0 ;
    }

    int Run(testParam1 &p) {
        int nCount = 0 ;
        IMModuleManager::singleton()->init() ;
        while(nCount++ < 4) {
           p.f() ;
           {
               print_log("thread %d time1 %ld \n" , pthread_self() , time(NULL)) ;
               mutex.Lock() ;
               event.Wait(mutex , 1000) ;
               mutex.Unlock() ;
               print_log("thread %d time2 %ld \n" , pthread_self() , time(NULL)) ;
           }
        }
        return 0 ;
    }


    int Run(testParam1 &p , testParam2 *p2 , testParam3 p3) {
        int nCount = 0 ;
        IMModuleManager::singleton()->init() ;
        while(nCount++ < 4) {
           p.f() ;
           p2->f() ;
           p3.f() ;
           {
               print_log("thread %d time1 %ld \n" , pthread_self() , time(NULL)) ;
               mutex.Lock() ;
               event.Wait(mutex , 1000) ;
               mutex.Unlock() ;
               print_log("thread %d time2 %ld \n" , pthread_self() , time(NULL)) ;
           }
           p3.t(this) ;
        }

        delete p2 ; 
        return 0 ;
    }

    int add(int a , int b) {
        return (a + b) ;
    }

    void signal() {
        mutex.Lock() ;
        event.SignalOne() ;
        mutex.Unlock() ;
    }

    void broadcast()  {
        mutex.Lock() ;
        event.SignalAll() ;
        mutex.Unlock() ;
    }

    std::list<SmartPtr<Thread> > threads ;
    Mutex  mutex ;
    Event  event ;
} ;


void testParam3::t(testThread *thr)
{
int r = thr->add(100 , 20) ;
print_log("r - %d = %d + %d \n" , r , 100 , 20) ;
}

int main()
{
    IMModuleManager::singleton()->init() ;
    ILog::singleton()->init("./") ;
    SmartPtr<IMSurfaceManagerClient> smc ;
    Mutex mutex ;
    Event event ;
    smc = IMSurfaceManagerClient::allocate() ;
    //for (int i = 0 ; i < 10 ; ++i)
    IMModuleManager::singleton()->init() ;

    IMSurfaceManager::singleton()->init() ;


    IMSurfaceManager::singleton()->exit() ;
    IMModuleManager::singleton()->exit() ;

    SmartPtr<testThread> t(new testThread()) ;
    t->Start() ;
    {
               print_log("thread %d time1 %ld \n" , pthread_self() , time(NULL)) ;
               ILog::singleton()->write("main" , 1 ,"thread %ld time1 %ld \n" , pthread_self() , time(NULL)) ;
               mutex.Lock() ;
               event.Wait(mutex , 1000) ;
               mutex.Unlock() ;
               print_log("thread %d time2 %ld \n" , pthread_self() , time(NULL)) ;
    }

    t->signal() ;

    {
               print_log("thread %d time1 %ld \n" , pthread_self() , time(NULL)) ;
               ILOG("main" , 1 ,"thread %ld time1 %ld \n" , pthread_self() , time(NULL)) ;
               mutex.Lock() ;
               event.Wait(mutex , 1000) ;
               mutex.Unlock() ;
               print_log("thread %d time2 %ld \n" , pthread_self() , time(NULL)) ;
    }

    t->broadcast() ;
    
    {
            print_log("thread %d time1 %ld \n" , pthread_self() , time(NULL)) ;
            mutex.Lock() ;
            event.Wait(mutex , 5000) ;
            mutex.Unlock() ;
            print_log("thread %d time2 %ld \n" , pthread_self() , time(NULL)) ;
    }

    ILOG_EXIT() ;
    return 0 ;
}