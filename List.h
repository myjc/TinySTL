#ifndef TINYSTL_LIST_H
#define TINYSTL_LIST_H
#include "Iterator.h"
#include "Allocator.h"
#include "Algorithm.h"
namespace TinySTL
{
template <typename T>
struct ListNode
{
    ListNode* preNode_;
    ListNode* nextNode_;
    T        data_;
    bool operator== (ListNode node)
    {
        return preNode_ == node.preNode_ && nextNode_ == node.nextNode_ && data_ == node.data_;
    }
};

template <typename T>
struct ListIterator:public iterator<bidirectional_iterator_tag,T>
{
public:
    typedef ListNode<T> Node;
    Node* nodePtr_;

public:
    //constructor
    explicit ListIterator(Node* ptr):nodePtr_(ptr){}
    ListIterator(const ListIterator& iter):nodePtr_(iter.nodePtr_){}
    ListIterator& operator=(const ListIterator &iter)
    {
        nodePtr_ = iter.nodePtr_;
        return *this;
    }

public:
    bool operator ==(const ListIterator& iter)
    {
        return nodePtr_ == iter.nodePtr_;
    }
    bool operator !=(const ListIterator& iter)
    {
        return nodePtr_ != iter.nodePtr_;
    }

    T& operator*(){ return (*nodePtr_).data_; }
    T* operator->(){ return &this->operator *();}
    ListIterator& operator++()
    {
        nodePtr_ = nodePtr_->nextNode_;
        return *this;
    }
    ListIterator operator++(int)
    {

        ListIterator tmp = *this;
        nodePtr_ = nodePtr_->nextNode_;
        return tmp;
    }
    ListIterator& operator--()
    {
        nodePtr_ = nodePtr_->preNode_;
        return *this;
    }
    ListIterator operator--(int)
    {

        ListIterator tmp = *this;
        nodePtr_ = nodePtr_->preNode_;
        return tmp;
    }
};
template <typename T,typename Alloc = alloc>
class List
{

public:
    typedef ListNode<T>         Node;
    typedef allocator<Node,Alloc>  NodeAllocator;
    typedef ListIterator<T>     iterator;
    typedef size_t              size_type;
    typedef T                   value_type;
    typedef T&                  reference;
    typedef T*                  pointer;
private:
    NodeAllocator allocator_;
    Node* nullNode_;
public:
    //constuctor
    List()
    {
        nullNode_ = get_node();
        nullNode_->nextNode_ = nullNode_;
        nullNode_->preNode_ = nullNode_;
    }
    ~List()
    {
        clear();
    }

public:
    iterator begin(){ return iterator(nullNode_->nextNode_);}
    iterator end(){ return iterator(nullNode_);}
    bool empty(){ return nullNode_->nextNode_ == nullNode_;}
    size_type size(){ return TinySTL::distance(begin(),end());}
    reference front(){ return *begin();}
    reference back(){ return *(--end());}
    void push_back(const T& val){ insert(end(),val); }
    void push_front(const T& val){ insert(begin(),val); }
    void pop_back()
    {
        iterator tmp = end();
        erase(--tmp);
    }
    void pop_front(){ erase(begin()); }
    iterator insert(iterator pos,const T& val)
    {
        //双向链表新节点插入
        Node* newNode = emplace_node(val);
        newNode->nextNode_ = pos.nodePtr_;
        newNode->preNode_ = pos.nodePtr_->preNode_;
        pos.nodePtr_->preNode_ = newNode;
        newNode->preNode_->nextNode_ = newNode;
        return iterator(newNode);
    }
    iterator insert(iterator pos, size_type n,const value_type& val);
    iterator erase(iterator pos)
    {
        iterator iter = pos;
        ++iter;
        pos.nodePtr_->preNode_->nextNode_ = iter.nodePtr_;
        iter.nodePtr_->preNode_ = pos.nodePtr_->preNode_;
        destroy_node(pos.nodePtr_);
        return iter;
    }
    iterator erase(iterator begin,iterator end);
    void clear()
    {
        erase(begin(),end());
    }
    void swap(List& x);
    void resize(size_type n,value_type value = T());
    void unique();
    void remove(const value_type& value);
    void splice(iterator position,List& x);
    void splice(iterator position, List&,iterator iter);
    void splice(iterator position, List &, iterator first,iterator last);
    void merge(List& x);
    void reverse();
    void sort();
private:
    Node* get_node()
    {
        return allocator_.allocate();
    }
    void put_node(Node* ptr){ allocator_.deallocate(ptr);}
    Node* emplace_node(const T& arg)
    {
        Node* tempNode = get_node();
        construct(&tempNode->data_,arg);
        return tempNode;
    }
    void destroy_node(Node* ptr)
    {
        destroy(&ptr->data_);
        put_node(ptr);
    }
    void transfer(iterator pos,iterator first,iterator last);


};
}
#endif // TINYSTL_LIST_H
