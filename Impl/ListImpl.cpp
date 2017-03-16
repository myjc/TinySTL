#ifndef TINYSTL_LISTIMPL_H
#define TIMYSTL_LISTIMPL_H
#include "../List.h"
namespace TinySTL
{
template<typename T,typename Alloc>
void List<T,Alloc>::swap(List &x)
{
    TinySTL::swap(nullNode_,x.nullNode_);
}

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
void List<T,Alloc>::splice(iterator position, List &x)
{
    if(!x.empty())
    {
        transfer(position,x.begin(),x.end());
    }
}
template<typename T,typename Alloc>
void List<T,Alloc>::splice(iterator position, List &, iterator iter)
{
    iterator next = iter;
    ++next;
    if(position == iter || position == next) return;
    transfer(position,iter,next);
}
template<typename T,typename Alloc>
void List<T,Alloc>::splice(iterator position, List &, iterator first, iterator last)
{
    if(first != last)
    {
        transfer(position,first,last);
    }
}
template<typename T,typename Alloc>
void List<T,Alloc>::merge(List<T,Alloc>& list1)
{
    iterator first1 = begin();
    iterator end1 = end();
    iterator first2 = list1.begin();
    iterator end2= list1.end();
    while(first1 != end1 && first2 != end2)
    {
        if(*first2 < *first1)
        {
            iterator next = first2;
            ++next;
            transfer(first1,first2,next);
            first2 = next;
        }
        else
        {
            ++first1;
        }
    }
    if(first2 != end2)
    {
        transfer(end1,first2,end2);
    }
}
template<typename T,typename Alloc>
void List<T,Alloc>::reverse()
{
    if(nullNode_->nextNode_ == nullNode_ || nullNode_->nextNode_->nextNode_ == nullNode_)
        return;
    iterator first = begin();
    ++first;
    while(first != end())
    {
        iterator old = first;
        ++first;
        transfer(begin(),old,first);
    }
}
template<typename T,typename Alloc>
void List<T,Alloc>::sort()
{
    if(nullNode_->nextNode_ == nullNode_ || nullNode_->nextNode_->nextNode_ == nullNode_)
        return;
    List<T,Alloc> carry;
    List<T,Alloc> counter[64];
    int fill = 0;
    while(!empty())
    {
        carry.splice(carry.begin(),*this,begin());
        int i = 0;
        for(;i < fill && !counter[i].empty();)
        {
            counter[i].merge(carry);
            carry.swap(counter[i]);
            i++;
        }
        carry.swap(counter[i]);
        if(i == fill)
            ++fill;
    }
    for(int i = 1; i < fill; i++)
    {
        counter[i].merge(counter[i - 1]);
    }
    swap(counter[fill - 1]);
}
}
#endif // TYNYSTL_LISTIMPL_H
