#ifndef TYPE_TRAITS_TPP
#define TYPE_TRAITS_TPP
#include <iostream>

namespace ft
{
    template <bool Cond, class T = void>
    struct enable_if
    {
    };

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template <class T, T v>
    struct integral_constant
    {
        static const T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
        operator T() { return v; }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <typename>
    struct is_integral
        : public false_type
    {
    };

    template <>
    struct is_integral<bool>
        : public true_type
    {
    };

    template <>
    struct is_integral<char>
        : public true_type
    {
    };

    template <>
    struct is_integral<signed char>
        : public true_type
    {
    };

    template <>
    struct is_integral<unsigned char>
        : public true_type
    {
    };

#ifdef _GLIBCXX_USE_WCHAR_T
    template <>
    struct is_integral<wchar_t>
        : public true_type
    {
    };
#endif

#ifdef _GLIBCXX_USE_CHAR8_T
    template <>
    struct is_integral<char8_t>
        : public true_type
    {
    };
#endif

    template <>
    struct is_integral<short>
        : public true_type
    {
    };

    template <>
    struct is_integral<unsigned short>
        : public true_type
    {
    };

    template <>
    struct is_integral<int>
        : public true_type
    {
    };

    template <>
    struct is_integral<unsigned int>
        : public true_type
    {
    };

    template <>
    struct is_integral<long>
        : public true_type
    {
    };

    template <>
    struct is_integral<unsigned long>
        : public true_type
    {
    };

    template <>
    struct is_integral<long long>
        : public true_type
    {
    };

    template <>
    struct is_integral<unsigned long long>
        : public true_type
    {
    };

}

#endif