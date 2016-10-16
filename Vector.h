#ifndef VECTOR_H
#define VECTOR_H
#include<functional>
#include<cstddef>
namespace TinySTL
{
template<typename T,typename Alloc = alloc> class Vector
{
public:
    typedef T value_type;
    typedef value_type* pointer;
    typedef value_type* iterator;
    typedef const value_type* const_iterator;
    typedef value_type& reference;
    typedef size_t size_type;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
protected:
    typedef allocator<value_type,Alloc> data_allocator;
private:
    iterator start;
    iterator finish;
    iterator end_of_storage;
public:
    //构造 析构 赋值
    Vector():start(nullptr),finish(nullptr),end_of_storage(nullptr){}
    explicit Vector(const size_type& objs);
    Vector(const size_type& objs,const value_type& value);
    Vector(const Vector& vec);
    Vector(Vector&& vec);
    template<typename InputIterator>
    Vector(InputIterator first,InputIterator last);

    Vector& operator =(const Vector& vec);
    Vector& operator =(Vector&& vec);

    ~Vector();
    //容量相关
    iterator begin(){return start;}
    iterator end() {return finish;}
    size_type size()const{return finish - start;}
    bool empty()const{return finish == start;}
    size_type capacity()const{return end_of_storage - start;}
    void resize(const size_type size, value_type val = value_type());
    void reserve(const size_type size);
    void shrink_to_fit();
    //容器操作
    reference operator[](const size_type index){return *(start+index);}
    reference at(const size_type index);
    void push_back(const value_type& value);

};//Vector
}//namesapce TinySTL
#endif // VECTOR_H
