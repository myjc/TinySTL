#ifndef TINYSTL_DEQUE_H
#define TINYSTL_DEQUE_H
#include "Allocator.h"
#include "Iterator.h"
#include "Algorithm.h"
#include "Uninitialize.h"
namespace TinySTL
{
inline size_t deque_buff_size(size_t n,size_t sz)
{
    if( n != 0) return n;
    return sz < 512 ? 512/sz : 1;
}

template<typename T,size_t BuffSize = 0>
class DequeIterator:public iterator<random_access_iterator_tag,T>
{
public:
    typedef typename iterator<random_access_iterator_tag,T>::value_type value_type;
    typedef typename iterator<random_access_iterator_tag,T>::pointer pointer;
    typedef typename iterator<random_access_iterator_tag,T>::difference_type difference_type;
    typedef typename iterator<random_access_iterator_tag,T>::reference reference;
    typedef typename iterator<random_access_iterator_tag,T>::iterator_category iterator_category;
    typedef DequeIterator self;
    typedef value_type** map_pointer;
private:
    value_type* cur_;
    value_type* first_;
    value_type* last_;
    map_pointer node_;
    static size_t buffer_size(){ return deque_buff_size(BuffSize,sizeof(T));}
    void setNode(map_pointer newNode)
    {
        node_ = newNode;
        first_ = *newNode;
        last_ = first_ + buffer_size();
    }

public:
    reference operator*(){ return *cur_;}
    pointer operator->(){ return &(operator *());}
    //distance of iterator
    difference_type operator-(const self& x) const
    {
        return difference_type(buffer_size()) * (node_-x.node_-1) +(cur_ - first_)+(x.last_-x.cur_);
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
    self operator--(int)
    {
        self tmp = *this;
        --*this;
        return tmp;
    }
    self& operator+=(difference_type n)
    {
        difference_type offset = n +(cur_ - first_);
        if(offset >= 0 && offset < buffer_size())
        {
            cur_ += n;
        }
        else
        {
            difference_type nodeOffset = 0;
            if(offset > 0)
                nodeOffset = offset / buffer_size();
            else
                nodeOffset = (offset + 1)/buffer_size() - 1;
            setNode(node_ + nodeOffset);
            cur_ = first_ + (offset - nodeOffset * buffer_size());
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
template<typename T,typename Alloc = alloc,size_t BuffSize = 0>
class Deque
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type& reference;
    typedef size_t size_type;
    typedef DequeIterator<T,BuffSize> iterator;
    typedef typename iterator::difference_type difference_type;
private:
    typedef pointer* map_pointer;
    typedef allocator<value_type,Alloc> data_allocator;
    typedef allocator<pointer,Alloc> map_allocator;
    data_allocator data_alloc_;
    map_allocator map_alloc_;
    iterator start_;
    iterator finish_;
    map_pointer map_;
    size_type map_size_;
public:
    Deque();
    Deque(int n ,const value_type& value);
    Deque(const Deque& deq);
    Deque(Deque&& deq);
    Deque& operator=(const Deque&);
    Deque& operator=(Deque&&);
    ~Deque(){ clear();}

public:
    iterator begin() { return start_;}
    iterator end() { return finish_;}
    reference operator[] (difference_type n){ return start_[n];}
    reference front(){ return *start_;}
    reference back() { return *(finish_ -1);}
    size_type size() const { return finish_ - start_ ;}
    bool empty() { return start_ == finish_;}
    void push_front(const value_type& value);
    void push_back(const value_type& value);
    void pop_front();
    void pop_back();
    void clear();
    iterator erase(iterator postion);
    iterator insert(iterator position,const value_type& value);
private:
    void fill_initialize(size_type n, const value_type& value);
    void create_map_and_nodes(size_type n);
    size_type buffer_size(){ return iterator::buffer_size();}
    static size_type initial_map_size(){ return 8;} //minimum map size;
    pointer allocate_node(){ return data_alloc_.allocate(buffer_size());}
    void push_back_aux(const value_type&);
    void push_front_aux(const value_type&);
    void pop_front_aux();
    void pop_back_aux();
    void insert_aux(iterator position, const value_type &value);
    void reserve_map_at_back(size_type nodes_to_add = 1);
    void reserve_map_at_front(size_type nodes_to_add = 1);
    void reallocate_map(size_type nodes_to_add,bool add_at_front);

};
}
#endif // TINYSTL_DEQUE_H
