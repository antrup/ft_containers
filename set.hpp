
#ifndef SET_HPP
# define SET_HPP
# include <memory>
# include <functional>
# include "utils.hpp"
# include <cstddef>
# include "iterator.hpp"
# include <stdint.h>
# include <limits>
# include "map.hpp"

namespace ft
{

template < typename T, typename Compare = std::less<T>, typename A = std::allocator<T> > 
class set
{

public:
    
    typedef T key_type;
    typedef T value_type;

    typedef Compare key_compare;
    typedef Compare value_compare; 

    typedef typename A::template rebind<map<T,T> >::other allocator_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference; 
    typedef typename A::pointer pointer; 
    typedef typename A::const_pointer const_pointer;
    
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;
    typedef typename map<T,T,Compare,allocator_type>::iterator mapIt;
    typedef typename map<T,T,Compare,allocator_type>::const_iterator const_mapIt;

    class iterator : public std::iterator<std::bidirectional_iterator_tag, mapIt, std::ptrdiff_t, const value_type*, const value_type&>
	{
	friend class set;
    public:
		iterator() {};
        iterator(mapIt p) 
        {
            itm = p;
        }
		iterator(iterator const & other) 
        {
            itm = other.itm;
        }
		~iterator() {}
		iterator & operator++() 
        {   
            ++itm;
            return (*this);
        }
        iterator operator++(int)
        {
            iterator temp_itt = iterator(this->itm);
            this->operator++();
            return (temp_itt);
        }

		iterator & operator--() 
        {
            --itm;
            return (*this);
        }
        iterator operator--(int)
        {
            iterator temp_itt = iterator(this->itm);
            this->operator--();
            return (temp_itt);
        }
		const value_type & operator*() const 
        {
            return itm.operator*().first;
        }
        const value_type * operator->() const
        {
            return &(itm.operator*().first);
        }
		bool operator==(const iterator & other) const 
        {
            return itm==other.itm;
        }
  		bool operator!=(const iterator & other) const 
        {
            return itm!=other.itm;
        }	
	protected:
		mapIt itm;
	};

    typedef iterator const_iterator;

    typedef ft::reverse_iterator<iterator> reverse_iterator;	
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    explicit set (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
    {
        mp = map<T,T,Compare,allocator_type>(comp, alloc);
        update_itt();
    }

    template <typename InputIterator>
    set (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
    {
        mp = map<T,T,Compare,allocator_type>(comp, alloc);
        InputIterator temp;
        temp = first;
        while (temp != last)
        {
            mp.insert(ft::make_pair(*temp, *temp));
            temp++;
        }
        update_itt();
    }

set (const set& x)
{
    mp = x.mp;
    update_itt();
}

set& operator= (const set& x)
{
    clear();
    if (x.begin_itt.itm == x.end_itt.itm)
        return (*this);
    insert(x.begin_itt, x.end_itt);
        return (*this);
}

private:

void update_itt()
{
    begin_itt.itm = mp.begin();
    end_itt.itm = mp.end();
}

public:

pair<iterator,bool> insert (const value_type& val)
{
    pair<mapIt, bool> ret = mp.insert(ft::make_pair(val,val));
    update_itt();
    return (ft::make_pair<iterator,bool>(iterator(ret.first), ret.second));
}

iterator insert (iterator position, const value_type& val)
{
    mapIt ret = mp.insert(position.itm,ft::make_pair(val,val));
    update_itt();
    return (iterator(ret));
}

template <class InputIterator>
void insert (InputIterator first, InputIterator last)
{
    if (first == last)
        return;
    InputIterator temp;
    temp = first;
    while (temp != last)
    {
        mp.insert(make_pair(*temp, *temp));
        temp++;
    }
    update_itt();
}

 iterator begin()
 {
     return (begin_itt);
 }
 
 const_iterator begin() const
 {
     return (begin_itt);
 }
 iterator end()
 {
     return (end_itt);
 }
 const_iterator end() const
 {
     return (end_itt);
 }

reverse_iterator rbegin() const
 {
    return (reverse_iterator(end_itt));
 }

reverse_iterator rend() const
{
    return (reverse_iterator(begin_itt));
}

size_t size() const
{
    return (mp.size());
}

size_type max_size() const
{
    return (mp.max_size());
}

void erase (iterator position)
{
    mp.erase(position.itm);
    update_itt();
}

size_type erase (const value_type& val)
{
    size_type ret = mp.erase(val);
    update_itt();
    return (ret);
}

void erase (iterator first, iterator last)
{
    if (first == last)
        return;
    iterator temp;
    iterator todel;
    temp = first;
    while (temp != last)
    {
        todel = temp++;
        mp.erase(todel.itm);
    }
    update_itt();
}

void clear()
{
    mp.clear();
    update_itt();
}

bool empty() const
{
    return (mp.empty());
}

void swap (set& x)
{
    mp.swap(x.mp);
    update_itt();
    x.update_itt(); 
}

private:
ft::map<T,T,Compare,allocator_type> mp;
iterator begin_itt;
iterator end_itt;
key_compare Comp;

public:

key_compare key_comp() const
{
    return (mp.key_comp());
}

value_compare value_comp() const
{
    return (mp.key_comp());
}

iterator find (const value_type& val) const
{
    const_mapIt ret = mp.find(val);
    const_mapIt &ret_ref = ret;
    mapIt &ret_m = reinterpret_cast<mapIt&>(ret_ref);
    return (iterator(ret_m));
}

size_type count (const value_type& val) const
{
    return (mp.count(val));
}

iterator lower_bound (const value_type& val) const
{
    iterator temp;

    temp = begin_itt;
    while (temp != end_itt)
    {
        if (!Comp(temp.itm.operator*().first, val))
                return (temp);
            temp++;
    }
    return (end_itt);
}

iterator upper_bound (const value_type& val) const
{
    iterator temp;

    temp = begin_itt;
    while (temp != end_itt)
    {
        if (Comp(val, temp.itm.operator*().first))
            return (temp);
        temp++;
    }
    return (end_itt);
}

pair<iterator,iterator> equal_range (const value_type& val) const
{
    return (ft::make_pair(lower_bound(val),upper_bound(val)));
}

allocator_type get_allocator() const
{
    return (allocator_type());
}

};
template <typename T, typename C, typename A>
bool operator== (const set<T,C,A>& lhs, const set<T,C,A>& rhs)
{
    
    if ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
        return true;
    return false;
}

template <typename T, typename C, typename A>
bool operator!= (const set<T,C,A>& lhs, const set<T,C,A>& rhs)
{
    return (!(lhs == rhs));
}

template <typename T, typename C, typename A>
bool operator<  (const set<T,C,A>& lhs, const set<T,C,A>& rhs)
{
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename T, typename C, typename A>
bool operator<= (const set<T,C,A>& lhs, const set<T,C,A>& rhs)
{
    if ((lhs == rhs) || (lhs < rhs))
        return true;
    return false;
}

template <typename T, typename C, typename A>
bool operator>  (const set<T,C,A>& lhs, const set<T,C,A>& rhs)
{
    return (!(lhs <= rhs));
}

template <typename T, typename C, typename A>
bool operator>= (const set<T,C,A>& lhs, const set<T,C,A>& rhs)
{
    return (!(lhs < rhs));
}

template <typename T, typename C, typename A>
void swap (set<T,C,A>& x, map<T,C,A>& y)
{
    x.swap(y);
}


}

#endif