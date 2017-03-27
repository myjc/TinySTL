#ifndef TINYSTL_UNORDERED_SET_H
#define TINYSTL_UNORDERED_SET_H
#include "Allocator.h"
#include "HashTable.h"
#include "Functional.h"
namespace TinySTL
{
    namespace // hash fucntions
    {
    template<typename T>struct hash{};

    template<>struct hash<char>
    {
        size_t operator()(char x){ return x;}
    };
    template<>struct hash<unsigned char>
    {
        size_t operator()(unsigned char x){ return x;}
    };
    template<>struct hash<signed char>
    {
        size_t operator()(signed char c){ return c;}
    };
    template<>struct hash<int>
    {
        size_t operator()(int c){ return c;}
    };
    template<>struct hash<long>
    {
        size_t operator()(long c){ return c;}
    };
    template<>struct hash<unsigned int>
    {
        size_t operator()(unsigned int c){ return c;}
    };
    template<>struct hash<unsigned long>
    {
        size_t operator()(unsigned long c){ return c;}
    };
    template<>struct hash<short>
    {
        size_t operator()(short c){ return c;}
    };
    template<>struct hash<unsigned short>
    {
        size_t operator()(unsigned short){ return c;}
    };
    inline string_hash(const char* str)
    {
        unsigned long result = 0;
        for(; *str != 0;++str)
        {
            result += 3*result + *str;
        }
    }

    template<>struct hash<char*>
    {
        size_t operator()(char* str)
        {
            return string_hash(str);
        }
    };
    template<>struct hash<const char*>
    {
        size_t operator()(char* str)
        {
            return string_hash(str);
        }
    };
    }
template<typename Value,typename HashFunc = hash<Value>,
         typename EqualFunc = EqualTo<Value>,typename Alloc = alloc>
class UnorderedSet
{
private:
    typedef HashTable<Value,Value,HashFunc,EqualFunc,Identity<Value>,Alloc> Table;
    Table table_;
public:
    typedef typename Table::value_type value_type;
    typedef typename Table::iterator iterator;
    typedef typename Table::size_type size_type;
    typedef typename Table::key_type key_type;
    typedef typename Table::reference reference;
    typedef typename Table::key_equal key_euqal;
    typedef typename Table::hasher hasher;
    typedef typename Table::local_iterator local_iterator;
public:
public:
    iterator begin(){ return table_.begin();}
    iterator end(){ return table_.end();}
    local_iterator begin(size_type index){ return table_.begin(index);}
    local_iterator end(size_type index){ return table_.end(index);}
    size_type size(){ return table_.size();}
    bool empty(){ return table_.empty();}
    Pair<iterator,bool> insert(const value_type& val){ return table_.insert_unique(val);}
    iterator find(const key_type& key){ return table_.find(key);}
    size_type count(const key_type& key){ return table_.count(key);}
    void clear(){ table_.clear();}
    void resize(size_type sz){ table_.rehash(sz);}
    size_type bucket_count(){ return table_.buckets_count();}
    size_type max_bucket_count(){ return table_.max_buckets_count();}
    void swap(UnorderedSet& set){ table_.swap(set.table_);}
};
}
#endif // UNORDERED_SET_H
