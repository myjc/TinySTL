#include "Deque.h"
namespace TinySTL
{
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::create_map_and_nodes(size_type num_element)
{
    size_type num_nodes = num_element / buffer_size() +1;
    map_size_ = TinySTL::max(initial_map_size(),num_nodes);
    map_ = map_alloc_.allocate(map_size_);
    map_pointer nstart = map_+(map_size_ - num_nodes)/2;
    map_pointer nfinish = nstart + num_nodes -1;
    map_pointer cur = nullptr;
    for(cur = nstart; cur < nfinish; ++cur)
    {
        *cur = allocate_node();
    }
    start_.setNode(nstart);
    finish_.setNode(nfinish);
    start_.cur_ = start_.first_;
    finish_.cur_ = finish_.first_ + num_element % buffer_size();
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::fill_initialize(size_type n, const value_type &value)
{
    create_map_and_nodes(n);
    map_pointer cur = nullptr;
    for(cur = start_.node_; cur < finish_.node_; ++cur)
    {
        TinySTL::uninitialized_fill(*cur,*cur+buffer_size(),value);
    }
    uninitialized_fill(finish_.first_, finish_.cur_, value);
}
template<typename T,typename Alloc,size_t Buffsize>
Deque<T,Alloc,Buffsize>::Deque(int n, const value_type& value)
{
    fill_initialize(n,value);
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::push_back(const value_type& value)
{
    if(finish_.cur_ != finish_.last_ -1)
    {
        construct(finish_.cur_,value);
        ++finish_.cur_;
    }
    else
    {
        push_back_aux(value);
    }
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::reallocate_map(size_type nodes_to_add,bool add_at_front)
{
    size_type old_nodes_num = finish_.node_ - start_.node_ +1;
    size_type new_nodes_num = old_nodes_num + nodes_to_add;
    map_pointer new_nstart = nullptr;
    if(map_size_ > 2 * new_nodes_num)
    {
        new_nstart = map_ + (map_size_ - new_nodes_num) /2
                +(add_at_front ? nodes_to_add : 0);
        if( new_nstart < start_.node_)
            copy(start_.node_,finish_.node_ +1,new_nstart);
        else
            copy_backward(start_.node_,finish_.node_ +1,new_nstart + old_nodes_num);
    }
    else
    {
        size_type new_map_size = map_size_ + max(map_size_,nodes_to_add)+2;
        map_pointer new_map = map_alloc_.allocate(new_map_size);
        new_nstart = new_map + (new_map_size - new_nodes_num) /2 +
                (add_at_front ? nodes_to_add : 0);
        copy(start_.node_,finish_.node_ +1, new_nstart);
        map_alloc_.deallocate(map_,map_size_);
        map_ = new_map;
        map_size_ = new_map_size;
    }
    start_.setNode(new_nstart);
    finish_.setNode(new_nstart + old_nodes_num -1);
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::reserve_map_at_back(size_type nodes_to_add)
{
    if(nodes_to_add > map_size_ - (finish_.node_ - map_ + 1))
        reallocate_map(nodes_to_add,false);
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::reserve_map_at_front(size_type nodes_to_add)
{
    if(nodes_to_add > start_.node_ - map_)
        reallocate_map(nodes_to_add,true);
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::push_back_aux(const value_type& value)
{
    value_type value_copy = value;
    reserve_map_at_back();
    *(finish_.node_ + 1) = allocate_node();
    construct(finish_.cur_,value_copy);
    finish_.setNode(finish_.node_ +1);
    finish_.cur_ = finish_.first_;
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::push_front(const value_type& value)
{
    if(start_.cur_ != start_.first_)
    {
        construct(start_.cur_ - 1,value);
        --start_.cur_;
    }
    else
    {
        push_front_aux(value);
    }
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::push_front_aux(const value_type& value)
{
    reserve_map_at_front();
    *(start_.node_ -1) = allocate_node();
    start_.setNode(start_.node_ -1);
    start_.cur_ = start_.last_ - 1;
    construct(start_.cur_,value);
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::pop_front()
{
    if(start_.cur_ != start_.last_ -1)
    {
        destroy(start_.cur_);
        ++start_.cur_;
    }
    else
        pop_front_aux();
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::pop_back()
{
    if(finish_.cur_ != finish_.first_)
    {
        --finish_.cur_;
        destroy(finish_.cur_);
    }
    else
        pop_back_aux();

}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::pop_front_aux()
{
    destroy(start_.cur_);
    if(start_.node_ != finish_.node_) //always true?
    {
        data_alloc_.deallocate(start_.first_, buffer_size());
        map_alloc_.destroy(start_.node_);
        start_.setNode(start_.node_ + 1);
        start_.cur_ = start_.first_;
    }
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::pop_back_aux()
{
    data_alloc_.deallocate(finish_.first_,buffer_size());
    if(finish_.node_ != start_.node_)//if not true, then it is an empty deque,nothing to do
    {
        finish_.setNode(finish_.node_ -1);
        finish_.cur_ = finish_.last_ -1;
        destroy(finish_.cur_);
    }
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::clear()
{
    for(map_pointer node = start_.node_ +1; node < finish_.node_; ++node)
    {
        destroy(*node,*node + buffer_size());
        data_alloc_.deallocate(*node,buffer_size());
    }
    if(start_.node_ != finish_.node_)
    {
        destroy(start_.cur_,start_.last_);
        destroy(finish_.first_, finish_.cur_);
        data_alloc_.deallocate(finish_.first_,buffer_size());
    }
    else
    {
        destroy(start_.cur_, finish_.cur_);
    }
    finish_ = start_;
}
template<typename T,typename Alloc,size_t Buffsize>
typename Deque<T,Alloc,Buffsize>::iterator Deque<T,Alloc,Buffsize>::erase(iterator pos)
{
    iterator next = pos;
    ++next;
    difference_type index = pos - start_;
    if(index < size() /2)
    {
        copy_backward(start_,pos,next);
        pop_front();
    }
    else
    {
        copy(next,finish_,pos);
        pop_back();
    }
    return start_ + index;
}
template<typename T,typename Alloc,size_t Buffsize>
typename Deque<T,Alloc,Buffsize>::iterator
Deque<T,Alloc,Buffsize>::insert(iterator pos,const value_type& val)
{
    if(pos == start_)
    {
        push_front(val);
        return start_;
    }
    else if(pos == finish_)
    {
        push_back(val);
        iterator tmp = finish_;
        return --tmp;
    }
    else
    {
        return insert_aux(pos,val);
    }
}
template<typename T,typename Alloc,size_t Buffsize>
void Deque<T,Alloc,Buffsize>::insert_aux(iterator pos,const value_type& val)
{
    difference_type index = pos - start_;
    if(index < size() /2)
    {
        push_front(front());
        iterator front1 = start_;
        ++front1;
        iterator front2 = front1;
        ++front2;
        iterator pos = start_ + index;
        ++pos;
        copy(front2,pos,front1);
    }
    else
    {
        push_back(back());
        iterator back1 = finish_;
        --back1;
        iterator back2 = back1;
        --back2;
        pos = start_ + index;
        copy_backward(pos,back2,back1);
    }
    *pos = val;
    return pos;
}
}//end of namespace
