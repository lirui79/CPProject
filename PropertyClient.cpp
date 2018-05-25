/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/05/10
**   File: PropertyClient.cpp
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#include "PropertyClient.h"
#include "Mutex.h"

namespace iris {

	PropertyClient::PropertyClient() {
    }

    PropertyClient::~PropertyClient() { 
    }

    SmartPtr<PropertyClient>& PropertyClient::singleton() {
        static Mutex mutex ;
        static SmartPtr<PropertyClient> singleton ;
        if (singleton != NULL)
            return singleton ;
        MutexLocker  locker(mutex) ;
        if (singleton == NULL)
        singleton = new PropertyClient() ;
        return singleton ;
    }

	/**
	 * 初始化模块内部参数，启动线程等
	 */
    int PropertyClient::init() {
        print_log("PropertyClient::init \n") ;
        return 0 ;
    }

	/**
	 * 退出模块内部线程，释放内存等
	 */
	int PropertyClient::exit() {
        print_log("PropertyClient::exit \n") ;
        return 0 ;
    }

	int PropertyClient::get(const char* key , int value) {

        print_log("PropertyClient::get Key int %s value %d \n" , key , value) ;
        return 10 ;
    }

	long PropertyClient::get(const char* key , long value) {

        print_log("PropertyClient::get Key long %s value %d \n" , key , value) ;
        return 10000 ;
    }

	bool PropertyClient::get(const char* key , bool value) {
        if(value)
            print_log("PropertyClient::get Key bool %s value true \n" , key) ;
        else
            print_log("PropertyClient::get Key bool %s value false \n" , key) ;

        return true ;
    }

	const char* PropertyClient::get(const char* key , const char* value) {
    
        print_log("PropertyClient::get Key string %s  value %s \n" , key , value) ;
        return "PropertyClient::get" ;
    }

	double PropertyClient::get(const char* key , double value) {    
        print_log("PropertyClient::get Key double %s value %f \n" , key , value) ;
        return 500.0f ;
    }

	int PropertyClient::get(const char* key , double *data , int &sz) {
          
        print_log("PropertyClient::get Key double array %s value %p sz %d \n" , key , data , sz) ;
        data[0] = 40.0f ;
        sz = 1 ;
        return 1 ;
    }

	int PropertyClient::set(const char* key, int value) {

        print_log("PropertyClient::set Key int %s value %d \n" , key , value) ;
        return 0 ;
    }

	int PropertyClient::set(const char* key, long value) {
        print_log("PropertyClient::set Key long %s value %d \n" , key , value) ;
        return 0 ;
    }

	int PropertyClient::set(const char* key, bool value) {
        if(value)
            print_log("PropertyClient::set Key bool %s value true \n" , key) ;
        else
            print_log("PropertyClient::set Key bool %s value false \n" , key) ;
        return 0 ;
    }

	int PropertyClient::set(const char* key, const char* value) {
        print_log("PropertyClient::set Key string %s  value %s \n" , key , value) ;
        return 0 ;
    }

	int PropertyClient::set(const char* key, double value) {
        print_log("PropertyClient::set Key double %s  value %f \n" , key , value) ;
        return 0 ;
    }

	int PropertyClient::set(const char* key, const double* data, int sz) {
          
        print_log("PropertyClient::set Key double array %s value %p sz %d \n" , key , data , sz) ;
        return 0 ;
    }

}



#if defined(__cplusplus)
extern "C" {
#endif

__attribute__((visibility("default"))) void*  allocatePropertyClient()
{
    return (void*) iris::PropertyClient::singleton().get();
}

#if defined(__cplusplus)
}
#endif