/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <atruphem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 15:17:26 by atruphem          #+#    #+#             */
/*   Updated: 2022/03/14 20:00:53 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <memory>
# include <cstddef>
# include <limits>
# include <cmath>
# include <stdexcept>
# include <typeinfo>
# include <iterator>
# include "iterator.hpp"
# include "utils.hpp"
# include <stdint.h>
# include <iostream>

namespace ft { 

template<typename T, typename A = std::allocator<T> >
class vector
{
public:
    typedef T value_type;	
    typedef A allocator_type; 

    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference; 
    typedef typename A::pointer pointer; 
    typedef typename A::const_pointer const_pointer;
    
    typedef T* iterator; 
    typedef const T* const_iterator; 
    typedef ft::reverse_iterator<iterator> reverse_iterator;	
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef std::ptrdiff_t difference_type;
    typedef std::size_t size_type;

    explicit vector(const allocator_type& a = allocator_type()) : Alloc(a)
    {
        Capacity = 0;
        Beg_itt = Alloc.allocate(10);
        End_itt = Beg_itt;
        Capacity = 10;
        Size = 0;    
        rBeg_itt = reverse_iterator(End_itt);
        rEnd_itt = reverse_iterator(Beg_itt);
    }

    explicit vector(size_type n, const value_type& val = value_type(), const allocator_type& a = allocator_type()) : Alloc(a)
    {
        Capacity = 0;
        if (n == 0)
        {
            Beg_itt = Alloc.allocate(10);
            End_itt = Beg_itt;
            Capacity = 10;
            Size = 0;    
            rBeg_itt = reverse_iterator(End_itt);
            rEnd_itt = reverse_iterator(Beg_itt);
            return;
        }
        Beg_itt = Alloc.allocate(n * 2);
        End_itt = Beg_itt + n;
        iterator i = Beg_itt;
        while (i != Beg_itt + n)
        {
            Alloc.construct(i, val);
            i++;
        }
        Capacity = n * 2;
        Size = n;
        rBeg_itt = reverse_iterator(End_itt);
        rEnd_itt = reverse_iterator(Beg_itt);
    }

    ~vector()
    {
        if (Capacity == 0)
            return;
        clear();
        Alloc.deallocate(Beg_itt, Capacity);
    }

    template <typename InputIterator>
    vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type& a = allocator_type()) : Alloc(a)
    {
        Capacity = 0;
        if (first == last)
        {
            Beg_itt = Alloc.allocate(10);
            End_itt = Beg_itt;
            Capacity = 10;
            Size = 0;    
            rBeg_itt = reverse_iterator(End_itt);
            rEnd_itt = reverse_iterator(Beg_itt);
            return;
        }
        vct_from_it(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
    }

protected:
    template <typename InputIterator>
    void vct_from_it(InputIterator first, InputIterator last, std::input_iterator_tag)
    {
        Beg_itt = Alloc.allocate(10);
        End_itt = Beg_itt;
        iterator i = Beg_itt;
        InputIterator j = first;
        Size = 0;
        Capacity = 10;
        while (j != last)
        {
            Alloc.construct(i, *j);
            i++;
            j++;
            Size++;
            End_itt++;
            if (Size == Capacity)
            {
                reserve(Capacity * 2);
                i = Beg_itt + Size;
                End_itt = i + 1;
            }
        }
        rBeg_itt = reverse_iterator(End_itt);
        rEnd_itt = reverse_iterator(Beg_itt);
    }
    
    template <typename InputIterator>
    void vct_from_it(InputIterator first, InputIterator last, std::forward_iterator_tag)
    {
        size_type distance = 0;
        InputIterator temp = first;
        while (temp != last)
        {    
            distance++;
            temp++;
        }
        vct_from_it_nav(first, distance);
    }
    
    template <typename InputIterator>
    void vct_from_it(InputIterator first, InputIterator last, std::random_access_iterator_tag)
    {    
        size_type distance = last - first;
        vct_from_it_nav(first, distance);
    }

    template <typename InputIterator>
    void vct_from_it_nav(InputIterator first, size_type distance)
    {    
        Beg_itt = Alloc.allocate(distance * 2);
        End_itt = Beg_itt + distance;
        rBeg_itt = reverse_iterator(End_itt);
        rEnd_itt = reverse_iterator(Beg_itt);
        iterator i = Beg_itt;
        InputIterator j = first;
        while (i != Beg_itt + distance)
        {
            Alloc.construct(i, *j);
            i++;
            j++;
        }
        Capacity = distance * 2;
        Size = distance; 
    }

public:
    vector(const vector& x)
    {
        if (x.Capacity == 0)
        {
            Beg_itt = Alloc.allocate(10);
        }
        else
        {
            Beg_itt = Alloc.allocate(x.Capacity);
        }
        End_itt = Beg_itt + x.Size;
        rBeg_itt = reverse_iterator(End_itt);
        rEnd_itt = reverse_iterator(Beg_itt);
        iterator i = Beg_itt;
        iterator j = x.Beg_itt;
        while (i != Beg_itt + x.Size)
        {
            Alloc.construct(i, *j);
            i++;
            j++;
        }
        Capacity = x.Capacity;
        Size = x.Size;
    }

    vector& operator= (const vector& x)
    {
        if (x.Beg_itt == x.End_itt)
            clear();
        else
            assign(x.Beg_itt, x.End_itt);
        return (*this);
    }

    iterator begin()
    {
        return (this->Beg_itt);
    }
    const_iterator begin() const
    {
        return (this->Beg_itt);
    }
    iterator end()
    {
        return (this->End_itt);
    }
    const_iterator end() const
    {
        return (this->End_itt);
    }
    reverse_iterator rbegin()
    {
        return (this->rBeg_itt);
    }
    const_reverse_iterator rbegin() const
    {
        return (this->rBeg_itt);
    }
    reverse_iterator rend()
    {
        return (this->rEnd_itt);
    }
    const_reverse_iterator rend() const
    {
        return (this->rEnd_itt);
    }

    size_type size() const
    {
        return (this->Size);
    }
    size_type max_size() const
    {
        if (INTPTR_MAX == INT32_MAX)
            return (4294967296 / sizeof(T));
        std::numeric_limits<size_t> lim; 
        return (lim.max() / sizeof(T)); 
    }
    
    void resize (size_type n, value_type val = value_type())
    {
        if (n < this->Size)
        {
            while (End_itt != Beg_itt + n)
                pop_back();
        }
        else
        {
            if (n > this->Capacity)
                reserve(n * 2);
            while (End_itt != Beg_itt + n)
                push_back(val);
        }
    }

    size_type capacity() const
    {
        return (this->Capacity);
    }

    bool empty() const
    {
        return (this->Size == 0);
    }

    void reserve(size_type n)
    {
        if (n > max_size())
            throw std::length_error("Size is greater than max size");            
        if (n > this->Capacity)
        {
            iterator nu = this->Alloc.allocate(n); 
            iterator ol = this->Beg_itt;
            iterator temp = nu;
            while (nu != temp + this->Size)
            {
                this->Alloc.construct(nu, *ol);
                this->Alloc.destroy(ol);
                nu++;
                ol++;
            }
            this->Alloc.deallocate(this->Beg_itt, this->Capacity);
            this->Beg_itt = temp;
            this->End_itt = temp + this->Size;
            this->Capacity = n;
            this->rBeg_itt = reverse_iterator(End_itt);
            this->rEnd_itt = reverse_iterator(Beg_itt);
        } 

    }

    reference operator[](size_type n)
    {
        return (*(this->Beg_itt + n));
    }
    const_reference operator[] (size_type n) const
    {
        return (*(this->Beg_itt + n));
    }
    reference at (size_type n)
    {
        if (n >= this->Size)
            throw std::out_of_range("Index invalid");
        return (*(this->Beg_itt + n));
    }
    const_reference at (size_type n) const
    {
        if (n >= this->Size)
            throw std::out_of_range("Index invalid");
        return (*(this->Beg_itt + n));
    }
    reference front()
    {
        return(*Beg_itt);
    }
    const_reference front() const
    {
        return(*Beg_itt);
    }
    reference back()
    {
        return(*(End_itt - 1));
    }
    const_reference back() const
    {
        return(*(End_itt - 1));
    }

    void clear()
    {
        iterator i = Beg_itt;
        while (i != End_itt)
        {
            this->Alloc.destroy(i);
            i++;
        }
        this->End_itt = this->Beg_itt;
        this->rBeg_itt = reverse_iterator(End_itt);
        this->rEnd_itt = reverse_iterator(Beg_itt);
        this->Size = 0;
    }

    template <typename InputIterator>
    void assign (typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
    {    
        this->clear();
        if (first == last)
            return;
        assign_from_it(first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
    }

protected:
    template <typename InputIterator>
    void assign_from_it(InputIterator first, InputIterator last, std::input_iterator_tag)
    {
        this->End_itt = Beg_itt + 1;
        iterator i = Beg_itt;
        InputIterator j = first;
        this->Size = 0;
        while (j != last)
        {
            if (this->Size == this->Capacity)
            {
                this->reserve(this->Capacity * 2 + 1);
                i = this->Beg_itt + this->Size;
                this->End_itt = i + 1;
            }
            this->Alloc.construct(i, *j);
            i++;
            j++;
            (this->Size)++;
            (this->End_itt)++;
        }
        this->rBeg_itt = reverse_iterator(this->End_itt);
        this->rEnd_itt = reverse_iterator(this->Beg_itt);
    }

    template <typename InputIterator>
    void assign_from_it(InputIterator first, InputIterator last, std::forward_iterator_tag)
    {
        size_type distance = 0;
        InputIterator temp = first;
        while (temp != last)
        {    
            distance++;
            temp++;
        }
        assign_from_it_nav(first, distance);
    }

    template <typename InputIterator>
    void assign_from_it(InputIterator first, InputIterator last, std::random_access_iterator_tag)
    {
        size_type distance = last - first;
        assign_from_it_nav(first, distance);
    }
    
    template <typename InputIterator>
    void assign_from_it_nav(InputIterator first, size_type distance)
    {    
        if (distance > this->Capacity)
        {
            this->Alloc.deallocate(this->Beg_itt, this->Capacity);
            this->Beg_itt = Alloc.allocate(distance * 2);
            this->rEnd_itt = reverse_iterator(this->Beg_itt);
            this->Capacity = distance * 2;
        }
        this->End_itt = this->Beg_itt + distance;
        this->rBeg_itt = reverse_iterator(this->End_itt);
        iterator i = this->Beg_itt;
        InputIterator j = first;
        while (i != this->Beg_itt + distance)
        {
            this->Alloc.construct(i, *j);
            i++;
            j++;
        }
        this->Size = distance; 
    }

public: 
void assign (size_type n, const value_type& val)
    {
        this->clear();
        if (n > this->Capacity)
        {
            this->Alloc.deallocate(this->Beg_itt, this->Capacity);
            this->Beg_itt = Alloc.allocate(n * 2);
            this->rEnd_itt = reverse_iterator(this->Beg_itt);
            this->Capacity = n * 2;
        }
        this->End_itt = this->Beg_itt + n;
        this->rBeg_itt = reverse_iterator(this->End_itt);
        iterator i = this->Beg_itt;
        while (i != this->Beg_itt + n)
        {
            Alloc.construct(i, val);
            i++;
        }
        this->Size = n;
    }

    void push_back (const value_type& val)
    {
        if (this->Size == this->Capacity)
            reserve(this->Capacity * 2 + 1);
        this->Alloc.construct(this->End_itt, val);
        Size++;
        End_itt++;
        this->rBeg_itt = reverse_iterator(this->End_itt);
    }

    void pop_back()
    {
        this->Alloc.destroy(this->End_itt - 1);
        Size--;
        End_itt--;
        this->rBeg_itt = reverse_iterator(this->End_itt);
    }

    iterator insert (iterator position, const value_type& val)
    {
        if (this->Size == this->Capacity)
        {
            iterator nu = this->Alloc.allocate(this->Size * 2 + 1); 
            iterator ol = this->Beg_itt;
            iterator temp = nu;
            while (ol != position)
            {
                this->Alloc.construct(nu, *ol);
                this->Alloc.destroy(ol);
                nu++;
                ol++;
            }
            iterator pos = nu;
            nu++;
            while (ol != this->End_itt)   
            {    
                this->Alloc.construct(nu, *ol);
                this->Alloc.destroy(ol);
                nu++;
                ol++;
            }
            this->Alloc.construct(pos, val);
            this->Alloc.deallocate(this->Beg_itt, this->Capacity);
            this->Beg_itt = temp;
            this->End_itt = this->Beg_itt + this->Size + 1;
            this->Capacity = this->Size * 2;
            this->rEnd_itt = reverse_iterator(this->Beg_itt);
            this->rBeg_itt = reverse_iterator(this->End_itt);
            (this->Size)++;
            return (pos);
        }
        else
        {
            iterator start = this->End_itt;
            while (start != position)
            {
                this->Alloc.construct(start, *(start - 1));
                this->Alloc.destroy(start - 1);
                start--;
            }
            this->Alloc.construct(position, val);
            End_itt++;  
            this->rBeg_itt = reverse_iterator(this->End_itt);
            Size++;
        }
        return (position);
    }

    void insert (iterator position, size_type n, const value_type& val)
    {
        if (n == 0)
            return;
        if (this->Capacity < this->Size + n)
        {
            iterator nu = this->Alloc.allocate(this->Size + (n * 2)); 
            iterator ol = this->Beg_itt;
            iterator temp = nu;
            while (ol != position)
            {
                this->Alloc.construct(nu, *ol);
                this->Alloc.destroy(ol++);
                nu++;
            }
            size_type add = n;
            while (add)
            {
                this->Alloc.construct(nu, val);
                nu++;
                add--;
            }
            while (ol != this->End_itt)   
            {    
                this->Alloc.construct(nu, *ol);
                this->Alloc.destroy(ol++);
                nu++;
            }
            this->Alloc.deallocate(this->Beg_itt, this->Capacity);
            this->Beg_itt = temp;
            this->End_itt = nu;
            this->Capacity = this->Size + (n * 2);
            this->rEnd_itt = reverse_iterator(this->Beg_itt);
            this->rBeg_itt = reverse_iterator(this->End_itt);
            this->Size = this->Size + n;
        }
        else
        {
            iterator start = this->End_itt + n - 1;
            while (start - n != position - 1)
            {
                this->Alloc.construct(start, *(start - n));
                this->Alloc.destroy(start - n);
                start--;
            }
            start++;
            size_type add = n;
            while (add)
            {
                this->Alloc.construct(start - add, val);
                add--;
            }
            this->End_itt = this->End_itt + n; 
            this->rBeg_itt = reverse_iterator(this->End_itt);
            this->Size = this->Size + n;
        }
    }

    template <class InputIterator>
    void insert (iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
    {
        if (first == last)
            return;
        insert_from_it(position, first, last, typename ft::iterator_traits<InputIterator>::iterator_category());
    }

protected:
    template <class InputIterator>
    void insert_from_it(iterator position, InputIterator first, InputIterator last, std::input_iterator_tag)
    {
        InputIterator i = first;
        iterator pos = position;
        while (i != last)
        {
            insert(pos, *i);
            i++;
            pos++;
        }
    }

    template <class InputIterator>
    void insert_from_it(iterator position, InputIterator first, InputIterator last, std::forward_iterator_tag)
    {
        size_type distance = 0;
        InputIterator temp = first;
        while (temp != last)
        {    
            distance++;
            temp++;
        }
        insert_from_it_nav(position, first, last, distance);
    }
    
    template <class InputIterator>
    void insert_from_it(iterator position, InputIterator first, InputIterator last, std::random_access_iterator_tag)
    {
        size_type distance = last - first;
        insert_from_it_nav(position, first, last, distance);
    }    
        
    template <class InputIterator>
    void insert_from_it_nav(iterator position, InputIterator first, InputIterator last, size_type distance)
    {
        if (this->Capacity <= this->Size + distance)
        {
            iterator nu = this->Alloc.allocate(this->Size + (distance * 2)); 
            iterator ol = this->Beg_itt;
            iterator temp = nu;
            while (ol != position)
            {
                this->Alloc.construct(nu, *ol);
                this->Alloc.destroy(ol);
                nu++;
                ol++;
            }
            InputIterator add = first;
            while (add != last)
            {
                this->Alloc.construct(nu, *add);
                nu++;
                add++;
            }
            while (ol != this->End_itt)   
            {    
                this->Alloc.construct(nu, *ol);
                this->Alloc.destroy(ol);
                nu++;
                ol++;
            }
            this->Alloc.deallocate(this->Beg_itt, this->Capacity);
            this->Beg_itt = temp;
            this->End_itt = nu;
            this->Capacity = this->Size + (distance * 2);
            this->rEnd_itt = reverse_iterator(this->Beg_itt);
            this->rBeg_itt = reverse_iterator(this->End_itt);
            this->Size = this->Size + distance;
        }
        else
        {
            iterator start = this->End_itt + distance - 1;
            while (start - distance != position - 1)
            {
                this->Alloc.construct(start, *(start - distance));
                this->Alloc.destroy(start - distance);
                start--;
            }
            InputIterator add = first;
            size_type n = distance - 1;
            while (add != last)
            {
                this->Alloc.construct(start - n, *add);
                add++;
                n--;
            }
            this->End_itt = this->End_itt + distance; 
            this->rBeg_itt = reverse_iterator(this->End_itt);
            this->Size = this->Size + distance;
        }
    }

public:
    iterator erase(iterator position)
    {
        this->Alloc.destroy(position);
        iterator start = position + 1;
        while (start != this->End_itt)
        {
            this->Alloc.construct(start - 1, *start);
            this->Alloc.destroy(start);
            start++;
        }
        (this->End_itt)--;
        this->rBeg_itt = reverse_iterator(this->End_itt);
        (this->Size)--;
        return (position);
    }

    iterator erase (iterator first, iterator last)
    {
        if (first == last)
            return (last);
        iterator start = first;
        while (start != last)
        {
            this->Alloc.destroy(start);
            start++;
        }
        iterator n = first;
        iterator realloc = last;
        while (realloc != this->End_itt)
        {
            this->Alloc.construct(n, *realloc);
            this->Alloc.destroy(realloc);
            realloc++;
            n++;
        }
        this->End_itt = n;
        this->rBeg_itt = reverse_iterator(this->End_itt);
        this->Size = this->End_itt - this->Beg_itt;
        return (first);
    }

    void swap (vector& x)
    {
        iterator Beg_itt_tp = this->Beg_itt;
        iterator End_itt_tp = this->End_itt;
        reverse_iterator rBeg_itt_tp = this->rBeg_itt;
        reverse_iterator rEnd_itt_tp = this->rEnd_itt;
        size_type Size_tp = this->Size;
        size_type Capacity_tp = this->Capacity;
        this->Beg_itt = x.Beg_itt;
        this->End_itt = x.End_itt;
        this->rBeg_itt = x.rBeg_itt;
        this->rEnd_itt = x.rEnd_itt;
        this->Size = x.Size;
        this->Capacity = x.Capacity;
        x.Beg_itt = Beg_itt_tp;
        x.End_itt = End_itt_tp;
        x.rBeg_itt = rBeg_itt_tp;
        x.rEnd_itt = rEnd_itt_tp;
        x.Size = Size_tp;
        x.Capacity = Capacity_tp;
    }

    allocator_type get_allocator() const
    {
        return(allocator_type());
    }

protected:
    allocator_type Alloc;
    iterator Beg_itt;
    iterator End_itt;
    reverse_iterator rBeg_itt;
    reverse_iterator rEnd_itt;
    size_type Size;
    size_type Capacity;
};

template <typename T, typename A>
bool operator== (const vector<T,A>& lhs, const vector<T,A>& rhs)
{
    
    if ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
        return true;
    return false;
}

template <typename T, typename A>
bool operator!= (const vector<T,A>& lhs, const vector<T,A>& rhs)
{
    return (!(lhs == rhs));
}

template <typename T, typename A>
bool operator<  (const vector<T,A>& lhs, const vector<T,A>& rhs)
{
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename T, typename A>
bool operator<= (const vector<T,A>& lhs, const vector<T,A>& rhs)
{
    if ((lhs == rhs) || (lhs < rhs))
        return true;
    return false;
}

template <class T, typename A>
bool operator>  (const vector<T,A>& lhs, const vector<T,A>& rhs)
{
    return (!(lhs <= rhs));
}

template <typename T, typename A>
bool operator>= (const vector<T,A>& lhs, const vector<T,A>& rhs)
{
    return (!(lhs < rhs));
}

template <typename T, typename A>
void swap (vector<T,A>& x, vector<T,A>& y)
{
    x.swap(y);
}

}

#endif