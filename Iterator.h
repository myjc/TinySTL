#ifndef ITERATOR_H
#define ITERATOR_H
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
struct _Iterator_Traits
{
    typedef typename I::iterator_category       iterator_category;
    typedef typename I::difference_type         difference_type;
    typedef typename I::value_type              value_type;
    typedef typename I::pointer                 pointer;
    typedef typename I::reference               reference;
};

//build in pointer

template<typename T>
struct _Iterator_Traits<T*>
{
    typedef random_access_iterator_tag          iterator_category;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef ptrdiff_t                           difference_type;

};

//const pointer
template<typename T>
struct _Iterator_Traits<const T*>
{
    typedef random_access_iterator_tag          iterator_category;
    typedef T                                   value_type;
    typedef T*                                  pointer;
    typedef T&                                  reference;
    typedef ptrdiff_t                           difference_type;

};

template<typename Iterator>
inline typename _Iterator_Traits<Iterator>::iterator_category iterator_category(const Iterator&)
{
    typedef typename _Iterator_Traits<Iterator>::iterator_category category;
    return category();
}

template<typename Iterator>
inline typename _Iterator_Traits<Iterator>::difference_type* distance_type(const Iterator&)
{
    return static_cast<typename _Iterator_Traits<Iterator>::difference_type*>(0);
}

template<typename Iterator>
inline typename _Iterator_Traits<Iterator>::value_type* value_type(const Iterator&)
{
    return static_cast<typename _Iterator_Traits<Iterator>::value_type*>(0);
}

}
#endif // ITERATOR_H
