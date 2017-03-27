#include "../HashTable.h"
namespace TinySTL
{
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
HashTableIterator<V,K,HF,ExK,EqK,Alloc>&
HashTableIterator<V,K,HF,ExK,EqK,Alloc>::operator++()
{
    ++cur_;
    if(cur_ == table_->buckets_[bk_index_].end())
    {
        size_type bk_size = table_->size();
        for(;bk_index_ < bk_size;++bk_index_)
        {
            if(!table_->buckets_[bk_index_].empty())
            {
                cur_ = table_->buckets_[bk_index_].begin();
                return *this;
            }
        }
        bk_index_ = bk_size -1;
        cur_ =table_->buckets_[bk_index_].end();
        return *this;
    }
    return *this;
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
HashTableIterator<V,K,HF,ExK,EqK,Alloc>
HashTableIterator<V,K,HF,ExK,EqK,Alloc>::operator++(int)
{
    HashTableIterator tmp = *this;
    ++*this;
    return tmp;
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
typename HashTable<V,K,HF,ExK,EqK,Alloc>::iterator
HashTable<V,K,HF,ExK,EqK,Alloc>::begin()
{
    size_type index = 0;
    for(; index < buckets_.size(); ++index)
    {
        if(!buckets_[index].empty())
            return iterator(buckets_[index].begin(),this);
    }
    return end();
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
typename HashTable<V,K,HF,ExK,EqK,Alloc>::local_iterator
HashTable<V,K,HF,ExK,EqK,Alloc>::begin(size_type n)
{
    return buckets_[n].begin();
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
typename HashTable<V,K,HF,ExK,EqK,Alloc>::iterator
HashTable<V,K,HF,ExK,EqK,Alloc>::end()
{
    return iterator(buckets_.back().end(),this);
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
typename HashTable<V,K,HF,ExK,EqK,Alloc>::local_iterator
HashTable<V,K,HF,ExK,EqK,Alloc>::end(size_type n)
{
    return buckets_[n].end();
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
typename HashTable<V,K,HF,ExK,EqK,Alloc>::size_type
HashTable<V,K,HF,ExK,EqK,Alloc>::buckets_index(const value_type& val,size_type n)
{
    return buckets_index_key(extractkey_(val),n);
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
typename HashTable<V,K,HF,ExK,EqK,Alloc>::size_type
HashTable<V,K,HF,ExK,EqK,Alloc>::buckets_index(const value_type& val)
{
    return buckets_index_key(extractkey_(val),buckets_.size());
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
typename HashTable<V,K,HF,ExK,EqK,Alloc>::size_type
HashTable<V,K,HF,ExK,EqK,Alloc>::buckets_index_key(const key_type& key,size_type n)
{
    size_type hash_val = hasher_(key);
    return hash_val % n;
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
typename HashTable<V,K,HF,ExK,EqK,Alloc>::size_type
HashTable<V,K,HF,ExK,EqK,Alloc>::buckets_index_key(const key_type& key)
{
    return buckets_index_key(key,buckets_.size());
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
void HashTable<V,K,HF,ExK,EqK,Alloc>::rehash(size_type num)
{
    const size_type old_size = buckets_.size();
    if(num <= max_load_factor_ * buckets_.size())
        return;
    const size_type new_size = next_prime(num);
    if(new_size <= old_size)
        return;
    Vector<List<value_type>> new_buckets(new_size,List<value_type>());
    for(size_type i = 0; i < old_size; ++i)
    {
        if(!buckets_[i].empty())
        {
            for(local_iterator iter = buckets_[i].begin();iter != buckets_[i].end();++iter)
            {
                size_type new_index = hasher_(extractkey_(*iter));
                new_buckets[new_index].splice(new_buckets[new_index].begin(),buckets_[i],iter);
            }
        }
    }
    buckets_.swap(new_buckets);
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
Pair<typename HashTable<V,K,HF,ExK,EqK,Alloc>::iterator,bool>
HashTable<V,K,HF,ExK,EqK,Alloc>::insert_unique(const value_type& val)
{
    rehash(num_elements_ + 1);
    size_type index = buckets_index(val);
    local_iterator iter = buckets_[index].begin();
    for(;iter != buckets_[index].end(); ++iter)
    {
        if(equaler_(extractkey_(val),extractkey_(*iter)))
            return Pair<iterator,bool>(iterator(iter,this,index),false);
    }
    buckets_[index].push_front(val);
    ++num_elements_;
    return Pair<iterator,bool>(iterator(buckets_[index].begin(),this,index),true);

}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
void HashTable<V,K,HF,ExK,EqK,Alloc>::clear()
{
    for(auto& list : buckets_)
    {
        if(!list.empty())
            list.clear();
    }
    num_elements_ = 0;
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
typename HashTable<V,K,HF,ExK,EqK,Alloc>::size_type
HashTable<V,K,HF,ExK,EqK,Alloc>::count(const key_type& key)
{
    size_type index = buckets_index_key(key);
    size_type result = 0;
    if(!buckets_[index].empty())
    {
        for(local_iterator iter = begin(index); iter != end(index); ++iter)
        {
            if(equaler_(extractkey_(*iter),key))
                ++result;
        }
    }
    return result;
}
template<typename V,typename K,typename HF,typename ExK,typename EqK,typename Alloc>
typename HashTable<V,K,HF,ExK,EqK,Alloc>::iterator
HashTable<V,K,HF,ExK,EqK,Alloc>::find(const key_type& key)
{
    size_type index = buckets_index_key(key);
    if(!buckets_[index].empty())
    {
        for(local_iterator iter = begin(index);iter != end(index);++iter)
        {
            if(equaler_(extractkey_(*iter),key))
                return iterator(iter,this,index);
        }
    }
    return end();
}
}//end namespace TinySTL
