#ifndef TINYSTL_TYPETRAITS_H
#define TINYSTL_TYPETRAITS_H


namespace TinySTL {
struct _true_type{};
struct _false_type{};

template<typename T>
struct _type_traits
{
    typedef _false_type has_trivial_default_constructor;
    typedef _false_type has_trivial_copy_constructor;
    typedef _false_type has_trivial_assignment_operator;
    typedef _false_type has_trivial_destructor;
    typedef _false_type is_POD_type;
};
//for build in type
template<> struct _type_traits<bool>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};

template<> struct _type_traits<int>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};

template<> struct _type_traits<unsigned int>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};

template<> struct _type_traits<long>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};

template<> struct _type_traits<unsigned long>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};

template<> struct _type_traits<short>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};
template<> struct _type_traits<unsigned short>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};

template<> struct _type_traits<char>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};
template<> struct _type_traits<signed char>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};
template<> struct _type_traits<unsigned char>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};
template<> struct _type_traits<float>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};
template<> struct _type_traits<double>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};
template<> struct _type_traits<long double>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};
// for bulid in pointer
template<typename T> struct _type_traits<T*>
{

    typedef _true_type has_trivial_default_constructor;
    typedef _true_type has_trivial_copy_constructor;
    typedef _true_type has_trivial_assignment_operator;
    typedef _true_type has_trivial_destructor;
    typedef _true_type is_POD_type;
};
//remove_reference
template<typename T>
struct RemoveReference
{
    typedef T type;
};
template<typename T>
struct RemoveReference<T&>
{
    typedef T type;
};
template<typename T>
struct RemoveReference<T&&>
{
    typedef T type;
};

template<typename T>
struct AddLvalueReference
{
    typedef T& type;
};
template<typename T>
struct AddRvalueReference
{
    typedef T&& type;
};

}

#endif // TINYSTL_H
