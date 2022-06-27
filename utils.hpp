/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <atruphem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:50:25 by atruphem          #+#    #+#             */
/*   Updated: 2022/02/09 19:02:01 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP
#include <functional>

namespace ft{

template<bool Cond, typename T = void>
struct enable_if {};

template<class T> 
struct enable_if<true, T> 
{ 
    typedef T type;
};

template <typename T> 
struct is_integral
{
    static const bool value = false;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<int>
{
    static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<bool>
{
    static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<char>
{
    static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<wchar_t>
{
   static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<signed char>
{
   static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<short int>
{
   static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<long int>
{
   static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<long long int>
{
   static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<unsigned int>
{
   static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<unsigned char>
{
   static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<unsigned short int>
{
   static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<unsigned long int>
{
   static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template<>
struct is_integral<unsigned long long int>
{
   static const bool value = true;
    operator bool()
    {
        return value;
    }
};

template <typename T1, typename T2> 
struct pair
{
public:    
    typedef T1 first_type;
    typedef T2 second_type;

    pair() : first(T1()), second(T2()) {};

    template<typename U, typename V> 
    pair (const pair<U,V>& pr) : first(pr.first), second(pr.second) {};

    pair (const first_type& a, const second_type& b) : first(a), second(b) {};

    pair& operator=(const pair& pr)
    {
        this->first = pr.first;
        this->second = pr.second;
        return (*this);
    }

    first_type first;
    second_type second;
};

template <typename T1, typename T2>
bool operator==(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ 
    return (lhs.first == rhs.first && lhs.second == rhs.second); 
}

template <typename T1, typename T2>
bool operator!=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ 
    return !(lhs == rhs); 
}

template <typename T1, typename T2>
bool operator<(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ 
    return (lhs.first < rhs.first || (!(rhs.first < lhs.first) && lhs.second < rhs.second)); 
}

template <typename T1, typename T2>
bool operator<=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ 
    return !(rhs < lhs); 
}

template <typename T1, typename T2>
bool operator>(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ 
    return rhs < lhs;
}

template <typename T1, typename T2>
bool operator>=(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
{ 
    return !(lhs<rhs); 
}

template <typename T1, typename T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{
    return (pair<T1,T2>(x,y));
}

}
#endif