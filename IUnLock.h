/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/05/24
**   File: IUnLock.h
**   Use:  one write thread and more than one read threads
**   Interface: get ->  read       set -> write
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef IUNLOCK_I_MODULE_H
#define IUNLOCK_I_MODULE_H

#include <atomic>
#include <vector>


template<typename T>
class IUnLock {
    private:
    struct Item {
        Item(const Item &item) : mRCount(0) , mValue(item.mValue) {

        }
        Item& operator=(const Item &item) {
            if (this == &item)
                return *this ;
            mValue = item.mValue ;
            return *this ;
        }

        Item() : mRCount(0) {}
        ~Item() {}
        T                mValue ;
        std::atomic<int> mRCount ;
    } ;
    public:
      IUnLock(int sz) : mSize(sz) , mVWrite(-1) {
          if (mSize < 3) 
            mSize = 3 ;
          mData.resize(mSize) ;
      }

      ~IUnLock() {
      }

      template<typename U>
      int  get(U &u , int (*fun)(const T &t , U &u) = NULL) {
            if (fun == NULL || mVWrite < 0) 
                return -1 ;
            long nVWrite = mVWrite ;
            nVWrite %= mSize ;
            Item *item = &mData[nVWrite] ;
            ++item->mRCount;
            int nCode = fun(item->mValue , u) ;
            --item->mRCount ;
            return 0 ;
      }

      int  get(T &t , int (*fun)(const T &tt , T &t) = NULL) {
            if (mVWrite < 0) 
                return -1 ;
            long nVWrite = mVWrite ;
            nVWrite %= mSize ;
            int nCode = 0 ;
            Item *item = &mData[nVWrite] ;
            ++item->mRCount;
            if (fun == NULL)
                t = item->mValue ;
            else
                nCode = fun(item->mValue , t) ;
            --item->mRCount;
            return nCode ;
      }

      template<typename U>
      int set(const U &u , int (*fun)(const U &u , T &t) = NULL) {
          if (fun == NULL)
             return -1 ;
          if (mVWrite < 0) {
              int nCode = fun(u , mData[0].mValue) ;
              mVWrite = 0 ;
              return nCode ;
          }
          long nVWrite = find() ;
          int nCode = fun(u , mData[nVWrite % mSize].mValue) ;
          mVWrite = nVWrite ;
          return nCode ;
      }

      int set(const T &t , int (*fun)(const T &t , T &tt) = NULL) {
          if (mVWrite < 0) {
              if (fun == NULL)  {
                mData[0].mValue = t ;
                mVWrite = 0 ;
                return 0 ;
              }

              int nCode = fun(t , mData[0].mValue) ;
              mVWrite = 0 ;
              return nCode ;
          }

          long nVWrite = find() ;
          if (fun == NULL) {
              mData[nVWrite % mSize].mValue = t ;
              mVWrite = nVWrite ;
              return 0 ;
          }

          int nCode = fun(t , mData[nVWrite % mSize].mValue) ;
          mVWrite = nVWrite ;
          return nCode ;
      }

    private:
      long   find() {
          long  nVWrite = mVWrite + 1 ;
          Item *items = &mData[mVWrite % mSize] ;
          while(true) {
                int nFind = 0 ;
                nVWrite = mVWrite + 1 ;
                for (int i = 1 ; i < mSize ; ++i , ++nVWrite)
                {
                    Item *item = &mData[nVWrite % mSize] ;
                    if (item->mRCount > 0)
                        continue ;
                    nFind = 1 ;
                    item->mValue = items->mValue ;
                    break ;
                }

                if (nFind == 1) 
                    break ;
          }

          return nVWrite;
      }

    private:
      std::vector<Item>     mData;
      int                   mSize ;
      std::atomic<long>     mVWrite ;
} ;


#endif //IUNLOCK_I_MODULE_H