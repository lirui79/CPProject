/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/04/08
**   File: IStatus.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef ISTATUS_I_MODULE_H
#define ISTATUS_I_MODULE_H

#include "Mutex.h"

namespace iris
{
class IMStatus : public virtual SmartObject
{
protected:
    typedef enum STATUS {
        NO   = 0 ,
        INIT = 1 , 
        RUN  = 2 , 
        EXIT = 3 
    } STATUS;
public:
    IMStatus() : mStatus(NO) , mExit(0) {
    }

    virtual ~IMStatus() {
    }

protected:
	virtual int get(STATUS status) {
        MutexLocker locker(mMutex) ;
		switch(status) {
			case INIT:
				switch (mStatus) {
					case NO:
						mStatus = INIT;
		        		mExit = 0;
						return  0;
					case INIT:
						return  1;
					case RUN:
						return  2;
					case EXIT:
						return -1;
					default:
						break;
				}
				break;
			case RUN:
				switch (mStatus) {
					case NO:
						return -1;
					case INIT:
						return -2;
					case RUN:
						return  0;
					case EXIT:
						return -3;
					default:
						break;
				}
				break;
			case EXIT:
				switch (mStatus) {
					case NO:
						return 2;
					case INIT:
						return -1;
					case RUN:
						mStatus = EXIT;
						mExit = 1 ;
						return 0 ;
					case EXIT:
						return 1;
					default:
						break;
				}
				break ;
			default:
				break ;
		}

		return -4;
	}
    
	/**
	 * return 0 is working 
	 **/
    virtual int work() {
        MutexLocker locker(mMutex) ;
        return mExit ;
    }

    virtual void set(STATUS status) {
        MutexLocker locker(mMutex) ;
        mStatus = status ;
    }

private:
    STATUS   mStatus ;
    Mutex    mMutex ;
    int      mExit ;
};

}  // namespace iris
#endif
