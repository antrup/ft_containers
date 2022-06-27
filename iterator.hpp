/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <atruphem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/18 15:39:16 by atruphem          #+#    #+#             */
/*   Updated: 2022/01/14 20:40:46 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITERATOR_HPP
# define ITERATOR_HPP
# include <cstddef>
# include <iterator>

namespace ft{

template <typename Iterator> 
class iterator_traits
{
public:
    typedef typename Iterator::difference_type difference_type;
    typedef typename Iterator::value_type value_type;
    typedef typename Iterator::pointer pointer;
    typedef typename Iterator::reference reference;
    typedef typename Iterator::iterator_category iterator_category;
};

template <typename T>
class iterator_traits<T*>
{
public:
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T* pointer;
    typedef T& reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template <typename T> 
class iterator_traits<const T*>
{
public:
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef const T* pointer;
    typedef const T& reference;
    typedef std::random_access_iterator_tag iterator_category;
};

template <typename Iterator> 
class reverse_iterator
{
public:
    typedef  Iterator iterator_type; //Iterator's type
    typedef  typename ft::iterator_traits<Iterator>::iterator_category iterator_category; //Preserves Iterator's category
    typedef  typename ft::iterator_traits<Iterator>::value_type value_type; //Preserves Iterator's value type
    typedef  typename ft::iterator_traits<Iterator>::difference_type difference_type; //Preserves Iterator's difference type
    typedef  typename ft::iterator_traits<Iterator>::pointer pointer; //Preserves Iterator's pointer type
    typedef  typename ft::iterator_traits<Iterator>::reference reference; //Preserves Iterator's reference type

    reverse_iterator(){};

    explicit reverse_iterator (iterator_type it)
    {
        _base = it;
    }

    template <typename Iter>
    reverse_iterator (const reverse_iterator<Iter>& rev_it)
    {
        _base = rev_it.base();
    }

    iterator_type base() const
    {
        return (this->_base);
    }

    reference operator*() const
    {
        Iterator temp = _base;
        return ((*(--temp)));
    }

    reverse_iterator operator+ (difference_type n) const
    {
        return (reverse_iterator(_base - n));
    }

    reverse_iterator& operator++()
    {
        (this->_base)--;
        return (*this);
    }

    reverse_iterator  operator++(int)
    {
        reverse_iterator temp = *this;
        (this->_base)--;
        return (temp);
    }

    reverse_iterator& operator+= (difference_type n)
    {
        this->_base -= n;
        return (*this);
    }

    reverse_iterator operator- (difference_type n) const
    {
        return (reverse_iterator(this->_base + n));
    }

    reverse_iterator& operator--()
    {
        (this->_base)++;
        return (*this);
    }

    reverse_iterator  operator--(int)
    {
        reverse_iterator temp = *this;
        (this->_base)++;
        return (temp);
    }

    reverse_iterator& operator-= (difference_type n)
    {
        this->_base += n;
        return (*this);
    }

    pointer operator->() const
    {
        return (&(operator*()));
    }

    reference operator[] (difference_type n) const
    {
        return (*(*this + n));
    }


private:
    iterator_type _base;
};

template <typename Iterator>
bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() == rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator== (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() == rhs.base());
}

template <typename Iterator>
bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() != rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator!= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() != rhs.base());
}

template <typename Iterator>
bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() > rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator< (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() > rhs.base());
}

template <typename Iterator>
bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() >= rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator<= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() >= rhs.base());
}

template <typename Iterator>
bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() < rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator> (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() < rhs.base());
}

template <typename Iterator>
bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (lhs.base() <= rhs.base());
}

template <typename Iterator1, typename Iterator2>
bool operator>= (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (lhs.base() <= rhs.base());
}

template <typename Iterator>
reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it)
{
    return (reverse_iterator<Iterator>(rev_it.base() - n));
}

template <typename Iterator>
typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs)
{
    return (rhs.base() - lhs.base());
}

template <typename Iterator1, typename Iterator2>
typename reverse_iterator<Iterator1>::difference_type operator- (const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs)
{
    return (rhs.base() - lhs.base());
}

template <typename InputIterator1, typename InputIterator2>
bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
{
    while (first1 != last1)
    {
        if (*first1 != *first2)
            return false;
        first1++;
        first2++;
    }
    return true;
}
	
template <typename InputIterator1, typename InputIterator2, typename BinaryPredicate>
  bool equal (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, BinaryPredicate pred)
{
    while (first1 != last1)
    {
        if (!pred(*first1, *first2))
            return false;
        first1++;
        first2++;
    }
    return true;
}

template <typename InputIterator1, typename InputIterator2>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2)
{
    while (first1 != last1)
    {
        if (first2 == last2)
            return false;
        else if (*first2 < *first1)
            return false;
        else if (*first1 < *first2)
            return true;
        first1++;
        first2++;
    }
    if (first2 == last2)
        return false;
    return true;
}

template <typename InputIterator1, typename InputIterator2, typename Compare>
bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1, InputIterator2 first2, InputIterator2 last2, Compare comp)
{
       while (first1 != last1)
    {
        if (first2 == last2)
            return false;
        else if (comp(*first2, *first1))
            return false;
        else if (comp(*first1,*first2))
            return true;
        first1++;
        first2++;
    }
    if (first2 == last2)
        return false;
    return true; 
}
}

#endif