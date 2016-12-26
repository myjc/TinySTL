#ifndef TINYSTL_ITERATOR_H
#define TINYSTL_ITERATOR_H
#include <cstddef> //for ptrdiff_t
namespace TinySTL {

// iterator type tag
struct input_iterator_tag{};
struct output_iterator_tag{};
struct forward_iterator_tag :public input_iterator_tag{};
struct bidirectional_iterator_tag :public forward_iterator_tag{};
struct random_access_iterator_tag :public bidirectional_iterator_tag{};

// base class
template<typename Category,typename T, typename Distance = ptrdiff_t,
         typename Pointer = T*,typename Reference = T&>
struct iterator
{
    typedef Category    iterator_category;
    typedef T           value_type;
    typedef Pointer     pointer;
    typedef Reference   reference;
    typedef Distance    difference_type;
};

//iterator traits

template<typename I>
struct IteratorTraits
{
    typedef typename I::iterator_category       iterator_category;
    typedef typename I::difference_type         difference_type;
    typedef typename I::value_type              value_type;
    typedef typename I::pointer                 pointer;
    typedef typename I::reference               reference;
};

//build in pointer

template<typename T>
struct IteratorTraits<T*>
{
    typedef random_access_iterator_tag          iterator_category;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef ptrdiff_t                           difference_type;

};

//const pointer
template<typename T>
struct IteratorTraits<const T*>
{
    typedef random_access_iterator_tag          iterator_category;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef ptrdiff_t                           difference_type;

};

template<typename Iterator>
inline typename IteratorTraits<Iterator>::iterator_category iterator_category(const Iterator&)
{
    typedef typename IteratorTraits<Iterator>::iterator_category category;
    return category();
}

template<typename Iterator>
inline typename IteratorTraits<Iterator>::difference_type* distance_type(const Iterator&)
{
    return static_cast<typename IteratorTraits<Iterator>::difference_type*>(0);
}

template<typename Iterator>
inline typename IteratorTraits<Iterator>::value_type* value_type(const Iterator&)
{
    return static_cast<typename IteratorTraits<Iterator>::value_type*>(0);
}
//reverse_iterator
template<typename Iterator>
class ReverseIterator
{
public:
    typedef ReverseIterator<Iterator> self;
    typedef Iterator iterator_type;
    typedef typename IteratorTraits<Iterator>::difference_type      difference_type;
    typedef typename IteratorTraits<Iterator>::iterator_category    iterator_category;
    typedef typename IteratorTraits<Iterator>::pointer              pointer;
    typedef typename IteratorTraits<Iterator>::reference            reference;
    typedef typename IteratorTraits<Iterator>::value_type           value_type;
protected:
    Iterator current_;
public:
    ReverseIterator() = default;
    explicit ReverseIterator(Iterator iter):current_(iter){}
    ReverseIterator(const self& iter):current_(iter.current_){}
    ReverseIterator& operator=(const self& iter)
    {
        current_ = iter.current_;
    }
    ~ReverseIterator() = default;
public:
    iterator_type base(){ return current_ ;}

public:

    reference operator* ()
    {
        Iterator tmp = current_;
        return *(--tmp);
    }
    pointer operator-> ()
    {
        return &(this->operator *());
    }
    self& operator++()
    {
        --current_;
        return *this;
    }
    self operator++(int)
    {
        self tmp = *this;
        --current_;
        return tmp;
    }
    self& operator--()
    {
        ++current_;
        return *this;
    }
    self operator--(int)
    {
        self tmp = *this;
        ++current_;
        return tmp;
    }

};
template <typename Iterator>
ptrdiff_t operator-(ReverseIterator<Iterator> lhv, ReverseIterator<Iterator> rhv)
{
    return lhv.base() - rhv.base();
}
}
#endif // TINYSTL_TERATOR_H
