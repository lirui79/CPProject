/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/05/09
**   File: PropertyClient.h
**   History:
**   Copy Right: iris corp
**
*/
/*****************************************************/
#ifndef IMODULE_PROPERTYCLIENT_H
#define IMODULE_PROPERTYCLIENT_H


#include "IMPropertyClient.h"

namespace iris {

class PropertyClient : public IMPropertyClient {
   private:
	PropertyClient(const PropertyClient& module);

	PropertyClient& operator=(const PropertyClient& module);

	PropertyClient();

   public:
	virtual ~PropertyClient();

	static SmartPtr<PropertyClient>& singleton();

	/**
	 * 初始化模块内部参数，启动线程等
	 */
	virtual int init();

	/**
	 * 退出模块内部线程，释放内存等
	 */
	virtual int exit();

	virtual int get(const char* key , int value = 0);

	virtual long get(const char* key , long value = 0);

	virtual bool get(const char* key , bool value = false);

	virtual const char* get(const char* key , const char* value = "");

	virtual double get(const char* key , double value = 0.0);

	virtual int get(const char* key , double *data , int &sz);

	virtual int set(const char* key, int value);

	virtual int set(const char* key, long value);

	virtual int set(const char* key, bool value);

	virtual int set(const char* key, const char* value);

	virtual int set(const char* key, double value);

	virtual int set(const char* key, const double* data, int sz);


	virtual const char* getClassName() const { return "PropertyClient"; }
};

}  // namespace iris

#endif