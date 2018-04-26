/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/29
**   File: Mutex.cpp
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#include "Mutex.h"

namespace iris
{
    Mutex::Mutex()    {
        pthread_mutex_init((pthread_mutex_t*)&mMutex_t, NULL );
    }

    Mutex::~Mutex(){
		pthread_mutex_destroy((pthread_mutex_t*)&mMutex_t);
	}

    int Mutex::Lock(){
		return pthread_mutex_lock((pthread_mutex_t*)&mMutex_t);
	}
    int Mutex::Unlock(){
		return pthread_mutex_unlock((pthread_mutex_t*)&mMutex_t);
	}
/*
    int Mutex::Trylock(){
		return pthread_mutex_trylock((pthread_mutex_t*)&mMutex_t);
	}*/

	MutexLocker::MutexLocker(Mutex& m):mMutex(m) {
		mMutex.Lock();
	}
    
	MutexLocker::~MutexLocker() {
		mMutex.Unlock();
	}

   Event::Event() : signal(false) {
        pthread_cond_init(&t, NULL);
    }

   Event::~Event() {
        signal = false ;
        pthread_cond_destroy(&t);
    }

   void Event::Time(unsigned long ms, struct timespec& now)    {
        while(clock_gettime(CLOCK_REALTIME, &now) != 0) 
            ; // -lrt 库

        ms += (unsigned long)(now.tv_nsec / 1000 /1000);
        now.tv_sec += ( ms / 1000) ;
        ms = (ms % 1000) ;
        /*while(ms >= 1000)
        {
            now.tv_sec++;
            ms -= 1000;
        }*/
        now.tv_nsec = ((long long)ms) * 1000 * 1000;
    }

    bool    Event::Wait(Mutex& m, unsigned long ms)    {
        bool bWait = true ;
        if (signal)
            bWait = true ;
        else
        {
            struct timespec now;
            Event::Time(ms, now);
            bWait = Wait(m, now);
        }
        signal = false ;
        return bWait ;
    }


    void    Event::SignalOne() {
        pthread_cond_signal(&t);
        signal = true ;
    }

    void Event::SignalAll() {
        pthread_cond_broadcast(&t);
        signal = true ;
    }

    bool    Event::Wait(Mutex& m, const struct timespec & tm)   {	
        return (0 == pthread_cond_timedwait(&t, &m.mMutex_t, &tm) ); // true - 非超时   false - 超时
    }


}