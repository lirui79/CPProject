/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/29
**   File: Mutex.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef MUTEX_MUTEX_LOCK_H
#define MUTEX_MUTEX_LOCK_H

#include <pthread.h>

namespace iris
{
class Mutex {
public:
    Mutex() ;

    ~Mutex() ;

    int Lock() ;

    int Unlock() ;

    //int Trylock() ;
private:
	friend class Event ;
	pthread_mutex_t mMutex_t;
};

class MutexLocker{
public:
	MutexLocker(Mutex& m);

	~MutexLocker() ;
private:
	Mutex& mMutex;
};

class Event 
{
protected:
    bool  signal ; 
    pthread_cond_t t;
public:
    Event() ;

    ~Event() ;

    static void Time(unsigned long ms, struct timespec& now) ;

    bool Wait(Mutex& m, unsigned long ms) ;

    void SignalOne() ;

    void SignalAll() ;

protected :
    bool Wait(Mutex& m, const struct timespec & tm) ;
}; 

}

#endif