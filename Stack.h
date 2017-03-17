#ifndef TINYSTL_STACK_H
#define TINYSTL_STACK_H
#include "Vector.h"
namespace TinySTL
{
template <typename T,typename SubContainer = Vector<T>>
class Stack
{
public:
    typedef typename SubContainer::value_type value_type;
    typedef typename SubContainer::reference reference;
    typedef typename SubContainer::size_type size_type;
    typedef SubContainer container_type;
    //
    explicit stack(const container_type& ctn = container_type()) :container_(ctn){}
    ~Stack() = default;
public:
    void push(const value_type& x)
    {
       container_.push_back(x);
    }
    void pop()
    {
        container_.pop_back();
    }
    reference top()
    {
        return container_.back();
    }
    const reference top() const
    {
        return container_.back();
    }
    bool empty()
    {
        return container_.empty();
    }
    size_type size() const
    {
        return container_.size();
    }
    void swap(Stack& st)
    {
        container_.swap(st.container_);
    }
public:
    template<typename T,typename Container>
    friend bool operator==(const Stack<T,Container>& st1,const Stack<T,Container>& st2);
    template<typename T,typename Container>
    friend bool operator!=(const Stack<T,Container>&,const Stack<T,Container>&);
private:
    container_type container_;
};
template<typename T,typename Container>
friend bool operator==(const Stack<T,Container>& st1,const Stack<T,Container>& st2)
{
    return st1.container_ == st2.container_;
}

template<typename T,typename Container>
friend bool operator!=(const Stack<T,Container>& st1,const Stack<T,Container>& st2)
{
    return st1.container_ != st2.container_;
}
}
#endif // TINYSTL_STACK_H
