#ifndef TINYSTL_DEQUE_H
#define TINYSTL_DEQUE_H
#include "Iterator.h"
namespace TinySTL
{
inline size_t dequeBuffSize(size_t n,size_t sz)
{
    if( n != 0) return n;
    return sz < 512 ? 512/sz : 1;
}

template<typename T,size_t BuffSize>
class DequeIterator:public iterator<random_access_iterator_tag,T>
{
public:
    typedef typename DequeIterator self;
    typedef value_type** map_pointer;
private:
    value_type* cur_;
    value_type* first_;
    value_type* last_;
    map_pointer node_;
    static size_t bufferSize(){ return dequeBuffSize(Buffsize,sizeof(T));}
    void setNode(map_pointer newNode)
    {
        node_ = newNode;
        first_ = *newNode;
        last_ = first_ + bufferSize();
    }

public:
    reference operator*(){ return *cur_;}
    pointer operator->(){ return &(operator *());}
    //distance of iterator
    difference_type operator-(const self& x) const
    {
        return difference_type(bufferSize()) * (node_-x.node_-1) +(cur_ - first_)+(x.last_-x.cur_);
    }
    self& operator++()
    {
        ++cur_;
        if(cur_ == last_)
        {
            setNode(node_ + 1);
            cur_ = first_;
        }
        return *this;
    }
    self operator++(int)
    {
        self tmp = *this;
        ++*this;
        return tmp;
    }
    self& operator--()
    {
        if(cur_ == first_)
        {
            setNode(node_ -1);
            cur_ = last_;
        }
        --cur_;
        return *this;
    }
    self operator--()
    {
        self tmp = *this;
        --*this;
        return tmp;
    }
    self& operator+=(difference_type n)
    {
        difference_type offset = n +(cur_ - first_);
        if(offset >= 0 && offset < bufferSize())
        {
            cur_ += n;
        }
        else
        {
            difference_type nodeOffset = 0;
            if(offset > 0)
                nodeOffset = offset / bufferSize();
            else
                nodeOffset = (offset + 1)/bufferSize() - 1;
            setNode(node_ + nodeOffset);
            cur_ = first_ + (offset - nodeOffset * bufferSize());
        }
        return *this;
    }
    self operator+(difference_type n)
    {
        self tmp = *this;
        return tmp += n;
    }
    self& operator-=(difference_type n)
    {
        return *this += -n;
    }
    self& operator-(difference_type n)
    {
        self tmp = *this;
        return tmp -= n;
    }
    reference operator[](difference_type n)
    {
        return *(*this += n);
    }
    bool operator==(const self& iter)const
    {
        return node_ == iter.node_ && cur_ == iter.cur_;
    }
    bool operator!=(const self& iter)const
    {
        return !(*this == iter);
    }
    bool operator<(const self& iter)const
    {
        return (node_ == iter.node_) ? (cur_ < iter.cur_) : (node_ < iter.node_);
    }
};
}
#endif // TINYSTL_DEQUE_H
