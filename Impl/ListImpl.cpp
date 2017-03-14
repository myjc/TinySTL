#ifndef TINYSTL_LISTIMPL_H
#define TIMYSTL_LISTIMPL_H
#include "../List.h"
namespace TinySTL
{
template<typename T,typename Alloc>
typename List<T,Alloc>::iterator
List<T,Alloc>::erase(iterator begin,iterator end)
{
    iterator before_begin = begin;
    --before_begin;
    before_begin.nodePtr_->nextNode_ = end;
    end.nodePtr_->preNode_ = before_begin.nodePtr_;
    while(begin != end)
    {
        destroy_node(begin.nodePtr_);
        ++begin;
    }
    return end;
}
template<typename T,typename Alloc>
typename List<T,Alloc>::iterator
List<T,Alloc>::insert(iterator pos,size_type n,const value_type& val)
{
    if(n == 0) return pos;
    iterator result =  insert(pos,val);
    for(int i = 0; i < n - 1; ++i)
    {
        insert(pos,val);
    }
    return result;
}
template<typename T,typename Alloc>
void List<T,Alloc>::resize(size_type n, value_type value)
{
    size_type length = distance(begin(),end());
    if(n == length)
        return;
    if(n < length)
    {
        iterator tmp = begin();
        advance(tmp,length);
        erase(tmp,end());
    }
    else
    {
        insert(end(),n-length,value);
    }
}
template<typename T,typename Alloc>
void List<T,Alloc>::unique()
{
    iterator first = begin();
    iterator last = end();
    if(first == last)
        return;
    iterator next = first;
    while(++next != last)
    {
        if(*first == *next)
            erase(next);
        else
            first = next;
        next = first;
    }
}
template<typename T,typename Alloc>
void List<T,Alloc>::remove(const value_type &value)
{
    iterator first = begin();
    iterator last = end();
    while(first != last)
    {
        iterator next = first;
        ++next;
        if(*first == value)
            erase(first);
        first = next;
    }
}
template<typename T,typename Alloc>
void List<T,Alloc>::transfer(iterator pos, iterator first, iterator last)
{
    last.nodePtr_->preNode_->nextNode_ = pos.nodePtr_;
    pos.nodePtr_->preNode_  ->nextNode_ = first.nodePtr_;
    first.nodePtr_->preNode_->nextNode_ = last.nodePtr_;
    Node* temp = last.nodePtr_->preNode_;
    last.nodePtr_->preNode_ = first.nodePtr_->preNode_;
    first.nodePtr_->preNode_ = pos.nodePtr_->preNode_;
    pos.nodePtr_->preNode_ = temp;
}

template<typename T,typename Alloc>
typename List<T,Alloc>::iterator
List<T,Alloc>::merge(iterator begin1,iterator end1,iterator begin2,iterator end2)
{
    if(begin1 == end1)
        return begin2;
    if(begin2 == end2)
        return begin1;
    Node* temp = get_node();
    Node* newhead = temp;
    while(begin1 != end1 && begin2 != end2)
    {
        if(*begin1 < *begin2)
        {
            temp->nextNode_ = begin1.nodePtr_;
            begin1.nodePtr_->preNode_ = temp;
            ++begin1;
        }
        else
        {
            temp->nextNode_ = begin2.nodePtr_;
            begin2.nodePtr_->preNode_ = temp;
            ++begin2;
        }
        temp = temp->nextNode_;
    }
    return iterator(newhead->nextNode_);
}
}
#endif // TYNYSTL_LISTIMPL_H
