/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <atruphem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 15:09:57 by atruphem          #+#    #+#             */
/*   Updated: 2022/02/21 16:35:11 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP
# include "vector.hpp"
# include <cstddef>

namespace ft{

template <typename T, typename Container = vector<T> >
class stack
{
public:
    typedef T value_type;
    typedef Container container_type;
    typedef size_t size_type;

    explicit stack (const container_type& ctnr = container_type()) : cont(ctnr) {}

    bool empty() const
    {
        return (cont.empty());
    }

    size_type size() const
    {
        return (cont.size());
    }

    value_type& top()
    {
        return (cont.back());
    }

    const value_type& top() const
    {
        return (cont.back());
    }

    void push (const value_type& val)
    {
        cont.push_back(val);
    }

    void pop()
    {
        cont.pop_back();
    }

    template <typename Ty, typename Conta>
    friend bool operator== (const stack<Ty,Conta>& lhs, const stack<Ty,Conta>& rhs);
    
    template <typename Ty, typename Conta>
    friend bool operator<  (const stack<Ty,Conta>& lhs, const stack<Ty,Conta>& rhs);

private:
    container_type cont;
    
};


template <typename T, typename Container>
bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return (lhs.cont == rhs.cont);
}  
template <typename T, typename Container>
bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return (!(lhs == rhs));
}  
template <typename T, typename Container>
bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return (lhs.cont < rhs.cont);
}  
template <typename T, typename Container>
bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    if ((lhs == rhs) || (lhs < rhs))
        return true;
    return false;
}  
template <typename T, typename Container>
  bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return (!(lhs <= rhs));
}  
template <typename T, typename Container>
bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
{
    return (!(lhs < rhs));
}  

    
}

#endif








