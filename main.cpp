#include "IMModuleManager.h"
#include "IMSurfaceManager.h"
#include "IMSurfaceManagerClient.h"
#include "PropertyClient.h"
#include "Mutex.h"
#include "Thread.h"
#include "ILog.h"
#include "IUnLock.h"

#include <unistd.h>
#include <list>

IUnLock<long> gTest(3) ;

struct testItem {
    char name[64] ;
    float  x ;
    float  y ;
    float  z ;
    int    id ;
} ;

IUnLock<struct testItem> gItem(3) ;

typedef std::vector<struct testItem> VectorItem ;

IUnLock<VectorItem> gVItem(3) ;

typedef std::list<struct testItem> ListItem ;

int copy_from_vetor_to_list(const VectorItem &vItems , ListItem &lItems) {
    if (vItems.empty())
        return 1 ;
    lItems.assign(vItems.begin() , vItems.end()) ;
    return 0 ;
}

int change_from_vector(const testItem &tItem , VectorItem &vItems) {
    if (vItems.empty())
        return -1 ;

    for (auto it = vItems.begin() ; it != vItems.end() ; ++it) {
        if (tItem.id != it->id)
            continue ;
        *it = tItem ;
        break ;
    }

    return 0 ;
}

int delete_from_vector(const testItem &tItem , VectorItem &vItems) {
    if (vItems.empty())
        return -1 ;

    for (auto it = vItems.begin() ; it != vItems.end() ; ++it) {
        if (tItem.id != it->id)
            continue ;
        vItems.erase(it) ;
        break ;
    }

    return 0 ;
}

int add_to_vector(const testItem &tItem , VectorItem &vItems) {
    if (vItems.empty())
        return -1 ;
    vItems.push_back(tItem) ;
    return 0 ;
}

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

    VectorItem items ;
    for (long i = 0 ; i < 100 ; ++i)
    {
        gTest.set(i) ;
        testItem  item ;
        sprintf(item.name , "testItem-%d" , i + 10000) ;
        item.x = 100. + 3 * i ;
        item.y = 10.5 + 2 * i ;
        item.z = -20 + 1.3 * i ;
        item.id = 0x2000 + 1000 * i ;
        items.push_back(item) ;
        gItem.set(item) ;
       print_log("0000000000 gTest %d - gItem.name %s id %d x %f y %f z %f\n", i , item.name , item.id , item.x , item.y , item.z) ;
    }

    gVItem.set(items) ;
    for (long i = 0 ; i < 100 ; ++i)
    {
        testItem  item ;
        sprintf(item.name , "testItem-%d" , i + 20000) ;
        item.x = 2000. + 3 * i ;
        item.y = 200.5 + 2 * i ;
        item.z = -400 + 1.3 * i ;
        item.id = 0x2000 + 1000 * i ;
        long n = i % 10 ;
        if (n < 3)
           gVItem.set(item , delete_from_vector) ;
        else if (n < 7)
           gVItem.set(item , change_from_vector) ;
        else
           gVItem.set(item , add_to_vector) ;
           
       print_log("44444444 gTest modify %d - gItem.name %s id %d x %f y %f z %f\n", n , item.name , item.id , item.x , item.y , item.z) ;
    }



        IMModuleManager::singleton()->init() ;
        return 1 ;
    }

    int Run() {

        int nCount = 0 ;
        testItem item ;
        long l ;
        for (long i = 0 ; i < 100 ; ++i) {
            gTest.get(l) ;
            gItem.get(item) ;
            print_log("111111111 gTest %d - %d gItem.name %s id %d x %f y %f z %f\n", i , l , item.name , item.id , item.x , item.y , item.z) ;
        }

        ListItem lItems ;
        for (long i = 0 ; i < 100 ; ++i) {
            gVItem.get(lItems , copy_from_vetor_to_list) ;
            print_log("55555555 gTest %d - %d gVItem size %d \n", i , l , lItems.size()) ;
        }

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
        testItem item ;
        long l ;
        for (long i = 0 ; i < 100 ; ++i) {
            gTest.get(l) ;
            gItem.get(item) ;
            print_log("222222222 gTest %d - %d gItem.name %s id %d x %f y %f z %f\n", i , l , item.name , item.id , item.x , item.y , item.z) ;
        }


        ListItem lItems ;
        for (long i = 0 ; i < 100 ; ++i) {
            gVItem.get(lItems , copy_from_vetor_to_list) ;
            print_log("66666666666666 gTest %d - %d gVItem size %d \n", i , l , lItems.size()) ;
        }
    
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
        testItem item ;
        long l ;
        for (long i = 0 ; i < 100 ; ++i) {
            gTest.get(l) ;
            gItem.get(item) ;
            print_log("33333333333 gTest %d - %d gItem.name %s id %d x %f y %f z %f\n", i , l , item.name , item.id , item.x , item.y , item.z) ;
        }

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
    {
        int ncode = 1 ;
        ncode = IMPropertyClient::singleton()->get("int" , (int)1) ;
        print_log("int ncode = %d\n" , ncode) ;
    }

    {
        long ncode = 21 ;
        ncode = IMPropertyClient::singleton()->get("long" , (long)21) ;
        print_log("long ncode = %d\n" , ncode) ;
    }

    {
        bool ncode = false ;
        ncode = IMPropertyClient::singleton()->get("bool" , (bool)false) ;
        print_log("bool ncode = %d\n" , ncode) ;
    }

    {
        const char *ncode = "321" ;
        const char* scode = IMPropertyClient::singleton()->get("string" , "ncode") ;
        print_log("string ncode = %s\n" , scode) ;
    }

    {
        double ncode = 4321.0f ;
        ncode = IMPropertyClient::singleton()->get("double" , (double)4321.0f) ;
        print_log("double ncode = %f\n" , ncode) ;
    }

    {
        double ncode[2] = {10.0f , 2000.0f} ;
        int sz = 2 ;
        sz = IMPropertyClient::singleton()->get("double array" , ncode , sz) ;
        print_log("double array ncode = %f %f %d\n" , ncode[0] , ncode[1] , sz) ;
    }


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
            event.Wait(mutex , 25000) ;
            mutex.Unlock() ;
            print_log("thread %d time2 %ld \n" , pthread_self() , time(NULL)) ;
    }

    ListItem lItems ;
    gVItem.get(lItems , copy_from_vetor_to_list) ;
    print_log("888888888 gTest gVItem size %d \n", lItems.size()) ;
    long i = 0 ;
    for (auto it = lItems.begin() ; it != lItems.end() ; ++it , ++i)
    {
        print_log("77777777777 lItems %d gItem.name %s id %d x %f y %f z %f\n", i , it->name , it->id , it->x , it->y , it->z) ;

    }

    ILOG_EXIT() ;
    return 0 ;
}