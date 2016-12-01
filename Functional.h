#ifndef TINYSTL_FUNCTIONAL_H
#define TINYSTL_FUNCTIONAL_H
namespace TinySTL
{
//base class of unary_function and binary_function
template<typename T,typename ResType>
struct UnaryFunctor
{
    typedef T       argument_type;
    typedef ResType result_type;
};

template<typename T1,typename T2, typename ResType>
struct BinaryFunctor
{
    typedef T1      first_argument_type;
    typedef T2      second_argument_type;
    typedef ResType result_type;
};
//关系运算，返回类型为bool
template<typename T>
struct Less:public BinaryFunctor<T,T,bool>
{
    bool operator() (const T& v1,const T& v2) const
    {
        return v1 < v2;
    }
};
template<typename T>
struct Greater:public BinaryFunctor<T,T,bool>
{
    bool operator() (const T& v1, const T& v2) const
    {
        return v1 > v2;
    }

};
template<typename T>
struct EqualTo:public BinaryFunctor<T,T,bool>
{
    bool operator() (const T& v1, const T& v2) const
    {
        return v1 == v2;
    }

};
template<typename T>
struct NotEqualTo:public BinaryFunctor<T,T,bool>
{
    bool operator() (const T& v1, const T& v2) const
    {
        return v1 != v2;
    }

};
template<typename T>
struct LessEqual:public BinaryFunctor<T,T,bool>
{
    bool operator() (const T& v1, const T& v2) const
    {
        return v1 <= v2;
    }

};
template<typename T>
struct GreaterEqual:public BinaryFunctor<T,T,bool>
{
    bool operator() (const T& v1, const T& v2) const
    {
        return v1 >= v2;
    }

};
//算术运算
template<typename T>
struct Plus:public BinaryFunctor<T,T,T>
{
    T operator()(const T& v1, const T& v2) const
    {
        return v1 + v2;
    }
};
template<typename T>
struct Minus:public BinaryFunctor<T,T,T>
{
    T operator()(const T& v1, const T& v2) const
    {
        return v1 - v2;
    }
};
template<typename T>
struct MultiPlies:public BinaryFunctor<T,T,T>
{
    T operator()(const T& v1, const T& v2) const
    {
        return v1 * v2;
    }
};
template<typename T>
struct Divides:public BinaryFunctor<T,T,T>
{
    T operator()(const T& v1, const T& v2) const
    {
        return v1 / v2;
    }
};
template<typename T>
struct Modulus:public BinaryFunctor<T,T,T>
{
    T operator()(const T& v1, const T& v2) const
    {
        return v1 % v2;
    }
};
template<typename T>
struct Negate:public UnaryFunctor<T,T>
{
    T operator()(const T& val) const
    {
        return -val;
    }
};
//逻辑运算
template<typename T>
struct LogicalAnd:public BinaryFunctor<T,T,bool>
{
    bool operator()(const T& v1, const T& v2) const
    {
        return v1 && v2;
    }
};
template<typename T>
struct LogicalOr:public BinaryFunctor<T,T,bool>
{
    bool operator()(const T& v1, const T& v2) const
    {
        return v1 || v2;
    }
};
template<typename T>
struct LogicalNot:public UnaryFunctor<T,bool>
{
    bool operator()(const T& v1) const
    {
        return  !v1;
    }
};
//位运算
template<typename T>
struct BitAnd :public BinaryFunctor<T,T,T>
{
    T operator()(const T& v1, const T& v2) const
    {
        return v1 & v2;
    }
};
template<typename T>
struct BitOr:public BinaryFunctor<T,T,T>
{
    T operator()(const T& v1, const T& v2) const
    {
        return v1 | v2;
    }
};
template<typename T>
struct BitXor:public BinaryFunctor<T,T,T>
{
    T operator()(const T& v1, const T& v2) const
    {
        return v1 ^ v2;
    }
};
template<typename T>
struct BitNot:public UnaryFunctor<T,T>
{
    T operator()(const T& val) const
    {
        return ~val;
    }
};
}//namespace TiynySTL
#endif // TINYSTL_FUNCTIONAL_H
