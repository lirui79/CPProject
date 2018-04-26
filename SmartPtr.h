/*****************************************************/
/*
**   Author: lirui
**   Date: 2018/03/29
**   File: SmartPtr.h
**   History: 
**   Copy Right: iris corp
**
/*****************************************************/

#ifndef SMART_PTR_H
#define SMART_PTR_H


namespace iris
{

typedef decltype(nullptr) nullptr_type;

template<typename T>
class SmartPtr {
public :
    explicit SmartPtr() : m_ptr(0) { }

    SmartPtr(T* other) : m_ptr(other) {
        if (m_ptr)
            m_ptr->RefCount(1) ;
    }

    SmartPtr(const SmartPtr<T>& other) : m_ptr(other.m_ptr) {
        if (m_ptr)
            m_ptr->RefCount(1) ;
    }

    template<typename U> 
    SmartPtr(U* other) : m_ptr(other) {
        if (m_ptr)
            m_ptr->RefCount(1) ;
    }

    template<typename U> 
    SmartPtr(const SmartPtr<U>& other) : m_ptr(other.m_ptr) {
        if (m_ptr)
            m_ptr->RefCount(1) ;
    }

    ~SmartPtr() {
        if (m_ptr)
            m_ptr->RefCount(0) ;
        m_ptr = 0 ;
    }

    SmartPtr& operator = (T* other) {
        reset(other) ;
        return *this;
    }

    SmartPtr& operator = (const SmartPtr<T>& other) {
        reset(other.m_ptr) ;
        return *this;
    }

    template<typename U> 
    SmartPtr& operator = (const SmartPtr<U>& other) {
        reset(other.m_ptr) ;
        return *this;
    }

    template<typename U> 
    SmartPtr& operator = (U* other) {
        reset(other) ;
        return *this;
    }

   // Reset
    void reset(T *other) {
        if (other == m_ptr)
            return ;
        if (m_ptr)
            m_ptr->RefCount(0) ;
        m_ptr = other;
        if (m_ptr)
            m_ptr->RefCount(1) ;
    }

    template<typename U>
    operator SmartPtr<U>()  {	// convert to compatible auto_ptr
        return (SmartPtr<U>(*this));
    }
    // Accessors

    inline  T&      operator*() const  { return *m_ptr; }

    inline  T*      operator->() const { return m_ptr;  }

    inline  T*      get() const         { return m_ptr; }

private: 
    template<typename Y> friend class SmartPtr;
    T* m_ptr;
} ;

template<typename _Tp1, typename _Tp2>
inline bool operator==(const SmartPtr<_Tp1>& __a, const SmartPtr<_Tp2>& __b)
{ return (__a.get() == __b.get()); }

template<typename _Tp>
inline bool operator==(const SmartPtr<_Tp>& __a, nullptr_type)
{ return (__a.get() == nullptr); }

template<typename _Tp>
inline bool operator==(nullptr_type, const SmartPtr<_Tp>& __a)
{ return (__a.get() == nullptr); }

template<typename _Tp1, typename _Tp2>
inline bool operator!=(const SmartPtr<_Tp1>& __a, const SmartPtr<_Tp2>& __b)
{ return (__a.get() != __b.get()); }

template<typename _Tp>
inline bool operator != (const SmartPtr<_Tp>& __a, nullptr_type)
{ return (bool) (__a.get() != nullptr) ; }

template<typename _Tp>
inline bool operator != (nullptr_type, const SmartPtr<_Tp>& __a)
{ return (bool) (__a.get() != nullptr); }

}

#endif