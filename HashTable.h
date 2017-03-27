#ifndef TINYSTL_HASH_TABLE_H
#define TINYSTL_HASH_TABLE_H
#include "Iterator.h"
#include "Allocator.h"
#include "Vector.h"
#include "List.h"
namespace TinySTL
{
//hashtable元素节点
template<typename T>
struct HashTableNode
{
    T data_;
    HashTableNode* nextNode_;
    HashTableNode():nextNode_(nullptr){}
};
//HashTable 前置声明
template<typename Value,typename Key,typename HashFunc,
         typename Extractkey,typename EqualKey,typename Alloc = alloc>
class HashTable;
//迭代器
template<typename Value,typename Key,typename HashFunc,
         typename Extractkey,typename EqualKey,typename Alloc>
class HashTableIterator
{
public:
    typedef forward_iterator_tag iterator_category;
    typedef Value           value_type;
    typedef value_type*     pointer;
    typedef value_type&     reference;
    typedef ptrdiff_t       difference_type;
    typedef size_t          size_type;
    typedef HashTableNode<Value> Node;
    typedef HashTable<Value,Key,HashFunc,Extractkey,EqualKey,Alloc> Table;
    typedef ListIterator<Value> local_iterator;

public:
    local_iterator cur_;
    Table* table_;
    size_type bk_index_;
public:
    HashTableIterator(local_iterator iter,Table* table,size_type index):
        cur_(iter),table_(table),bk_index_(index){}
    HashTableIterator() = default;
    ~HashTableIterator() = default;
    reference operator*(){ return *cur_;}
    pointer operator->(){return &(operator*());}
    HashTableIterator& operator++();
    HashTableIterator operator++(int);
    bool operator==(const HashTableIterator& iter){return cur_ = iter.cur_;}
    bool operator!= (const HashTableIterator& iter){return cur_ != iter.cur_;}

};
template<typename Value,typename Key,typename HashFunc,
         typename Extractkey,typename EqualKey,typename Alloc>
class HashTable
{
public:
    typedef size_t size_type;
    typedef Value value_type;
    typedef Key   key_type;
    typedef HashTableIterator<Value,Key,HashFunc,Extractkey,EqualKey,Alloc> iterator;
    typedef typename iterator::difference_type difference_type;
    typedef typename iterator::pointer pointer;
    typedef typename iterator::reference reference;
    typedef typename List<Value>::iterator local_iterator;
    typedef HashFunc hasher;
    typedef EqualKey key_equal;
private:
    hasher     hasher_;
    Extractkey   extractkey_;
    key_equal     equaler_;
    Vector<List<Value>> buckets_;
    size_type num_elements_;
    float max_load_factor_;

public:
    HashTable():max_load_factor_(1.0){}
    HashTable(size_type n,const HashFunc& hashfunc,const EqualKey& eql)
    {
        initialize_buckets(n);
    }
    ~HashTable(){ clear();}
public:
    size_type buckets_count(){ return buckets_.size();}
    size_type buckets_size(size_type index){ return buckets_[index].size();}
    iterator begin();
    iterator end();
    local_iterator begin(size_type n);
    local_iterator end(size_type n);
    size_type count(const key_type&);
    iterator find(const key_type&);
    size_type size()const{ return num_elements_;}
    bool empty()const{ return num_elements_ == 0;}
    float load_factor(){ return static_cast<float>(num_elements_) / buckets_.size();}
    size_type max_load_factor() { return max_load_factor_;}
    void max_load_factor(float factor){ max_load_factor_ = factor;}
    Pair<iterator,bool> insert_unique(const value_type&);
    iterator insert_equal(const value_type&);
    void clear();
    void swap(HashTable& ht)
    {
        buckets_.swap(ht.buckets_);
        TinySTL::swap(num_elements_,ht.num_elements_);
        TinySTL::swap(max_load_factor_,ht.max_load_factor_);
    }

private:
    static const int stl_num_prime_ = 28;
    constexpr static const unsigned int primes_list[stl_num_prime_] =
    {
        53,97,193,389,769,1543,3079,6151,12289,24593,49157,98317,196613,393241,786433,1572869,
        3145739,6291469,1258917,25165843,50331653,100663919,201326611,402653189,805306457,
        1610612741,3221225473,4294967291
    };
    unsigned long next_prime(unsigned long n)
    {
        const unsigned long* first = primes_list;
        const unsigned long* last = primes_list + stl_num_prime_;
        const unsigned long* pos = TinySTL::lower_bound(first,last,n);
        return pos == last ? *(last - 1) : *pos;
    }
    size_type max_buckets_count(){ return primes_list[stl_num_prime_ - 1];}
    void rehash(size_type num);
    void initialize_buckets(size_type n)
    {
        const size_type size = next_prime(n);
        buckets_.reserve(n);
        buckets_.insert(buckets_.end(),size,List<Value>());
    }
    size_type buckets_index(const value_type& val,size_type n);
    size_type buckets_index(const value_type& val);
    size_type buckets_index_key(const key_type& val,size_type n);
    size_type buckets_index_key(const key_type& val);
};
}
#endif // TINYSTL_HASH_TABLE_H
