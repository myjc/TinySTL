#ifndef TINYSTL_H
#define TINYSTL_H


namespace TinySTL {
    struct _True_Type{};
    struct _False_Type{};

    template<typename T>
    struct __Type_Traits
    {
        typedef _False_Type has_trivial_default_constructor;
        typedef _False_Type has_trivial_copy_constructor;
        typedef _False_Type has_trivial_assignment_operator;
        typedef _False_Type is_POD_type;
    };
    //for build in type
    template<> struct __Type_Traits<bool>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };

    template<> struct __Type_Traits<int>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };

    template<> struct __Type_Traits<unsigned int>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };

    template<> struct __Type_Traits<long>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };

    template<> struct __Type_Traits<unsigned long>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };

    template<> struct __Type_Traits<short>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };
    template<> struct __Type_Traits<unsigned short>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };

    template<> struct __Type_Traits<char>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };
    template<> struct __Type_Traits<signed char>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };
    template<> struct __Type_Traits<unsigned char>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };
    template<> struct __Type_Traits<float>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };
    template<> struct __Type_Traits<double>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };
    template<> struct __Type_Traits<long double>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };
    // for bulid in pointer
    template<typename T> struct __Type_Traits<T*>
    {

        typedef _True_Type has_trivial_default_constructor;
        typedef _True_Type has_trivial_copy_constructor;
        typedef _True_Type has_trivial_assignment_operator;
        typedef _True_Type is_POD_type;
    };


}

#endif // TINYSTL_H
