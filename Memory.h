#ifndef TINYSTL_MEMORY_H
#define TINYSTL_MEMORY_H
#include <cstddef>
#include "Utility.h"
namespace TinySTL
{
template<typename ElementType>
class SharedPtr
{
private:
    ElementType* dataPtr_;
    size_t* useCount_;
public:
    //构造析构相关
    SharedPtr() = default;

    explicit SharedPtr(ElementType* ptr):dataPtr_(ptr),useCount_(new size_t(1)){}

    SharedPtr(const SharedPtr& sptr):dataPtr_(sptr.dataPtr_),
                                     useCount_(sptr.useCount_){++*useCount_;}
    SharedPtr& operator= (const SharedPtr& sptr)
    {
        ++ (*sptr.useCount_);
        if(--*useCount_ == 0)
        {
            delete dataPtr_;
            delete useCount_;
        }
        dataPtr_ = sptr.dataPtr_;
        useCount_ = sptr.useCount_;
        return *this;
    }
    ~SharedPtr()
    {
        if(--*useCount_ == 0)
        {
            delete dataPtr_;
            delete useCount_;
        }
    }
public:
    //
    ElementType* get()const{return dataPtr_;}
    void swap(SharedPtr& sptr)
    {
        ElementType* elePtr =dataPtr_;
        size_t* use = useCount_;
        dataPtr_ = sptr.dataPtr_;
        useCount_ = sptr.useCount_;
        sptr.dataPtr_ = elePtr;
        sptr.useCount_ = use;
    }
    bool unique()const{ return *useCount_ == 1;}
    size_t use_count()const{ return *useCount_;}
    void reset()
    {
        if(--*useCount_ == 0)
        {
            delete dataPtr_;
            delete useCount_;
        }
        dataPtr_ = nullptr;
    }
    void reset(ElementType* ptr)
    {
        if(--*useCount_ == 0)
        {
            delete dataPtr_;
            delete useCount_;
        }
        dataPtr_ = ptr;
        useCount_ = new size_t(1);
    }

public:
    //操作符
    ElementType operator* (){ return *dataPtr_; }
    ElementType* operator-> (){return &this->operator*();}
    bool operator==(const SharedPtr& sptr)
    {
        return (dataPtr_ == sptr.dataPtr_ ) && (useCount_ == sptr.useCount_);
    }
    bool operator!=(const SharedPtr& sptr){ return !(*this == sptr);}
    operator bool()const{return (dataPtr_ != nullptr);}//类型转换
};
template<typename T,typename...Args> SharedPtr<T> makeShared(const Args& ...args)
{
    return SharedPtr<T>(new T(TinySTL::forward<Args>(args)...));
}
template<typename T> inline void swap(SharedPtr<T>& s1, SharedPtr<T>& s2)
{
    s1.swap(s2);
}
}
namespace TinySTL
{
template<typename T>
struct DefaultDeleter
{
    void operator() (T* ptr)
    {
        delete ptr;
        ptr = nullptr;
    }
};

template<typename T,typename Deleter = DefaultDeleter>
class UniquePtr
{
public:
    typedef T ElementType;
    UniquePtr() = default;
    explicit UniquePtr(ElementType* ptr):elementPtr(ptr){}
    explicit UniquePtr(Deleter del):deleter(del){}
    UniquePtr(const UniquePtr& up) = delete;
    UniquePtr(UniquePtr&& up)
    {
        elementPtr = up.elementPtr;
    }

    UniquePtr operator=(UniquePtr &&up) = delete;

    UniquePtr& operator=(std::nullptr_t)
    {
        deleter(elementPtr);
        elementPtr = nullptr;
    }

    ~UniquePtr()
    {
        deleter(elementPtr);
    }
public:
    ElementType& operator*()
    {
        return *elementPtr;
    }
    ElementType* operator->()
    {
        return &this->operator *();
    }
    ElementType* get(){return elementPtr;}
    ElementType* release()
    {
        ElementType* tmp = elementPtr;
        elementPtr = nullptr;
        return tmp;
    }
    void reset(){deleter(elementPtr);}
    void reset(ElementType* ptr)
    {
        deleter(elementPtr);
        elementPtr = ptr;
    }
    void reset(std::nullptr_t)
    {
        deleter(elementPtr);
        elementPtr = nullptr;
    }


    void swap(UniquePtr& up)
    {
        ElementType* tmpPtr = elementPtr;
        elementPtr = up.elementPtr;
        up.elementPtr = tmpPtr;
    }


private:
    ElementType* elementPtr;
    Deleter deleter;
};
template<typename T>
void swap(UniquePtr<T>p1,UniquePtr<T>p2)
{
    p1.swap(p2);
}
}

#endif // TinySTL_MEMORY_H
