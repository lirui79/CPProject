/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/29
**   File: SmartObject.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef SMART_OBJECT_H
#define SMART_OBJECT_H


namespace iris
{

class SmartObject {
private :
    SmartObject(const SmartObject &ref) ;
    SmartObject& operator=(const SmartObject &ref) ;
protected :
    SmartObject() ;
    virtual ~SmartObject() ;
public :
    int  RefCount(int type = 0) ;

    virtual const char*  getClassName() const ;
private :
     int mRefCount ;
};

void print_log(const char *format , ...) ;
}

#endif