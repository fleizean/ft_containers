#ifndef TYPE_TRAITS_HPP
#define TYPE_TRAITS_HPP

#include "iterator_base.hpp"
#include <cstdint>

namespace ft
{
    template <bool Cond, typename T = void>
    struct enable_if {};

    template <typename T>
    struct enable_if<true, T> { typedef T type; };

    struct false_type
    {
        typedef bool value_type;
        typedef false_type type;
        static const value_type value = false;
    };

    struct true_type
    {
        typedef bool value_type;
        typedef true_type type;
        static const value_type value = true;
    };

template <class T>
    struct is_integral : public false_type {};
    template <class T>
    struct is_integral<const T> : public is_integral<T> {};
    template <class T>
    struct is_integral<volatile const T> : public is_integral<T> {};
    template <class T>
    struct is_integral<volatile T> : public is_integral<T> {};
    template<>
    struct is_integral<unsigned char> : public true_type {};
    template<>
    struct is_integral<unsigned short> : public true_type {};
    template<>
    struct is_integral<unsigned int> : public true_type {};
    template<>
    struct is_integral<unsigned long> : public true_type {};
    template <>
    struct is_integral<signed char> : public true_type {};
    template <>
    struct is_integral<short> : public true_type {};
    template <>
    struct is_integral<int> : public true_type {};
    template <>
    struct is_integral<long int> : public true_type {};
    template <>
    struct is_integral<long long int> : public true_type {};
    template <>
    struct is_integral<unsigned long long int> : public true_type {};
    template <>
    struct is_integral<char> : public true_type {};
    template <>
    struct is_integral<bool> : public true_type {};

}

#endif