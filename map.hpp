/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atruphem <atruphem@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/09 17:50:18 by atruphem          #+#    #+#             */
/*   Updated: 2022/03/11 16:46:39 by atruphem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAP_HPP
# define MAP_HPP
# include <memory>
# include <functional>
# include "utils.hpp"
# include <cstddef>
# include "iterator.hpp"
# include <stdint.h>
# include <limits>

namespace ft {

enum	e_rb_color
{
	RB_BLACK,
	RB_RED
};

template <typename Key, typename T>
struct s_node : ft::pair<Key, T>
{
    struct	s_node	    *parent;
	struct	s_node	    *left;
	struct	s_node	    *right;
	enum	e_rb_color	color;
    s_node() : pair<Key, T>(Key(), T()), color(RB_RED)
    {
        parent = NULL;
        left = NULL;
        right = NULL;
    }
    s_node(Key keyword, T value) : pair<Key, T>(keyword, value), color(RB_RED)
    {
        parent = NULL;
        left = NULL;
        right = NULL;
    }
};

template <typename Key, typename T, typename Compare = std::less<Key>, typename A = std::allocator<pair<const Key,T> > > 
class map
{
public:
    typedef Key key_type;
    typedef T mapped_type;

    typedef pair<const key_type, mapped_type> value_type;
    typedef Compare key_compare;
    class value_compare : public std::binary_function<value_type, value_type, bool>
    {
        friend class map;
        public:
            bool operator()(const value_type& one, const value_type& two)
            {
                return (comp(one.first, two.first));
            }
        private:
            Compare comp;
            value_compare(Compare cmp) : comp(cmp) {}
    };

    typedef typename A::template rebind<struct s_node<const Key,T> >::other allocator_type;
    typedef typename A::reference reference;
    typedef typename A::const_reference const_reference;
    typedef typename A::pointer pointer;
    typedef typename A::const_pointer const_pointer;

private:
    typedef s_node<const key_type, mapped_type> node;

public:
    class iterator : public std::iterator<std::bidirectional_iterator_tag, node, std::ptrdiff_t, value_type*, value_type&>
	{
	friend class map;
    public:
		iterator() 
        {
            ptr = NULL;
        }
		iterator(node* p) 
        {
            ptr = p;
        }
		iterator(iterator const & other) 
        {
            ptr = other.ptr;
        }
		template <typename Container>
        iterator(typename Container::iterator const & other)
        {
            ptr = &(*other);
        }
		~iterator() {}
		iterator & operator++() 
        {   
            if (ptr->right)
            {
                ptr = ptr->right; 
                while (ptr->left)
                    ptr = ptr->left;
            }
            else if (ptr == ptr->parent->left)
            {
                ptr = ptr->parent;
            }
            else
            {
                while (ptr == ptr->parent->right)
                    ptr = ptr->parent;
                ptr = ptr->parent;
            }
            return (*this);
        }
        iterator operator++(int)
        {
            iterator temp_itt = iterator(this->ptr);
            this->operator++();
            return (temp_itt);
        }

		iterator & operator--() 
        {
            if (ptr->left)
            {
                ptr = ptr->left; 
                while (ptr->right)
                    ptr = ptr->right;
            }
            else if (ptr == ptr->parent->right)
            {
                ptr = ptr->parent;
            }
            else
            {
                while (ptr == ptr->parent->left)
                    ptr = ptr->parent;
                ptr = ptr->parent;
            }
            return (*this);
        }
        iterator operator--(int)
        {
            iterator temp_itt = iterator(this->ptr);
            this->operator--();
            return (temp_itt);
        }
		value_type & operator*() const 
        {
            return *ptr;
        }
        value_type * operator->() const
        {
            return ptr;
        }
		bool operator==(const iterator & other) const 
        {
            return ptr==other.ptr;
        }
  		bool operator!=(const iterator & other) const 
        {
            return ptr!=other.ptr;
        }	
	protected:
		node* ptr;
	};
    
    class const_iterator : public std::iterator<std::bidirectional_iterator_tag, node, std::ptrdiff_t, const value_type*, const value_type&>
	{
	friend class map;
    public:
		const_iterator() 
        {
            ptr = NULL;
        }
		const_iterator(node* p)
        {
            ptr = p;
        }
        const_iterator(const node* p)
        {
            ptr = p;
        }
		const_iterator(const iterator & other) 
        {
            ptr = other.ptr;
        }
		template <typename Container>
        const_iterator(typename Container::iterator const & other)
        {
            ptr = &(*other);
        }
		~const_iterator() {}
		const_iterator & operator++() 
        {   
            if (ptr->right)
            {
                ptr = ptr->right; 
                while (ptr->left)
                    ptr = ptr->left;
            }
            else if (ptr == ptr->parent->left)
            {
                ptr = ptr->parent;
            }
            else
            {
                while (ptr == ptr->parent->right)
                    ptr = ptr->parent;
                ptr = ptr->parent;
            }
            return (*this);
        }
        const_iterator operator++(int)
        {
            const_iterator temp_itt = const_iterator(this->ptr);
            this->operator++();
            return (temp_itt);
        }
		const_iterator & operator--() 
        {
            if (ptr->left)
            {
                ptr = ptr->left; 
                while (ptr->right)
                    ptr = ptr->right;
            }
            else if (ptr == ptr->parent->right)
            {
                ptr = ptr->parent;
            }
            else
            {
                while (ptr == ptr->parent->left)
                    ptr = ptr->parent;
                ptr = ptr->parent;
            }
            return (*this);
        }
        const_iterator operator--(int)
        {
            const_iterator temp_itt = const_iterator(this->ptr);
            this->operator--();
            return (temp_itt);
        }
		const value_type & operator*() const
        {
            return *ptr;
        }
        const value_type * operator->() const
        {
            return ptr;
        }
		bool operator==(const const_iterator & other) const 
        {
            return ptr==other.ptr;
        }
  		bool operator!=(const const_iterator & other) const 
        {
            return ptr!=other.ptr;
        }
		bool operator==(const iterator & other) const 
        {
            return ptr==other.ptr;
        }
  		bool operator!=(const iterator & other) const 
        {
            return ptr!=other.ptr;
        }	
	protected:
		const node* ptr;
    };
    
    typedef ft::reverse_iterator<iterator> reverse_iterator;	
    typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : Alloc(alloc), Comp(comp)
    {
        head = Alloc.allocate(1);
        begin_itt = iterator(head);
        end_itt = begin_itt;
        rend_itt = end_itt;
        Alloc.construct(head, node());
        Size = 0;
    }
    
    template <typename InputIterator>
    map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()) : Alloc(alloc), Comp(comp)
    {
        if (first == last)
        {
            head = Alloc.allocate(1);
            begin_itt = iterator(head);
            end_itt = begin_itt;
            rend_itt = end_itt;
            Alloc.construct(head, node());
            Size = 0;
            return;
        }
        InputIterator temp;
        node *ntemp;

        ntemp = Alloc.allocate(1);
        end_itt = iterator(ntemp);
        Alloc.construct(ntemp, node());
        ntemp = Alloc.allocate(1);
        rend_itt = iterator(ntemp);
        Alloc.construct(ntemp, node());
        ntemp = Alloc.allocate(1);
        begin_itt = iterator(ntemp);
        Alloc.construct(ntemp, node((*first).first, (*first).second));
        head = ntemp;
        ntemp->color = RB_BLACK;
        ntemp->right = end_itt.ptr;
        ntemp->left = rend_itt.ptr;
        end_itt.ptr->parent = ntemp;
        rend_itt.ptr->parent = ntemp;
        temp = first;
        temp++;
        Size = 1;
        while (temp != last)
        {
            insert(*temp);
            temp++;
        }
    }

    map (const map& x) : Alloc(x.Alloc), Comp(x.Comp)
    {
        head = Alloc.allocate(1);
        begin_itt = iterator(head);
        end_itt = begin_itt;
        rend_itt = end_itt;
        Alloc.construct(head, node());
        Size = 0;
        if (x.begin_itt.ptr == x.end_itt.ptr)
            return;
        insert(x.begin_itt, x.end_itt);
    }

    map& operator= (const map& x)
    {
        clear();
        if (x.begin_itt.ptr == x.end_itt.ptr)
            return (*this);
        insert(x.begin_itt, x.end_itt);
        return (*this);
    }

    ~map()
    {
        clear();
        Alloc.destroy(head);
        Alloc.deallocate(head, 1);
    }
    
    iterator begin()
    {
        return (this->begin_itt);
    }
    const_iterator begin() const
    {
        return (this->begin_itt);
    }
    iterator end()
    {
        return (this->end_itt);
    }
    const_iterator end() const
    {
        return (this->end_itt);
    }

    reverse_iterator rbegin() const
    {
        return (reverse_iterator(end_itt));
    }

    reverse_iterator rend() const
    {
        return (reverse_iterator(begin_itt));
    }

    pair<iterator,bool> insert (const value_type& val)
    {
        node *temp;
        node *new_node;

        if ((temp = rb_search(&(val.first))))
            return (pair<iterator,bool>(iterator(temp), false));
        
        temp = head;
	    while (temp)
	    {
            if (temp == end_itt.ptr)
            {
                    new_node = Alloc.allocate(1);
                    Alloc.construct(new_node, node(val.first, val.second));
                    new_node->right = temp;
                    if (temp->parent)
                    {
                        temp->parent->right = new_node;
                        new_node->parent = temp->parent;
                    }
                    temp->parent = new_node;
                    if (temp->left)
                    {
                        new_node->left = temp->left;
                        temp->left->parent = new_node;
                        temp->left = NULL;
                    }
                    if (temp == head)
                    {
                        rend_itt.ptr = Alloc.allocate(1);
                        Alloc.construct(rend_itt.ptr, node());
                        rend_itt.ptr->parent = new_node;
                        new_node->left = rend_itt.ptr;
                        head = new_node;
                    }
		    		temp = NULL;
            }
            else if (temp == rend_itt.ptr)
            {
                    new_node = Alloc.allocate(1);
                    Alloc.construct(new_node, node(val.first, val.second));
                    new_node->left = temp;
                    if (temp->parent)
                    {
                        temp->parent->left = new_node;
                        new_node->parent = temp->parent;
                    }
                    temp->parent = new_node;
                    if (temp->right)
                    {
                        new_node->right = temp->right;
                        temp->right->parent = new_node;
                        temp->right = NULL;
                    }
                    temp = NULL;
            }
		    else if (Comp(temp->first, val.first))         
		    {	
                if(temp->right == NULL)
		    	{
		    		new_node = Alloc.allocate(1);
                    Alloc.construct(new_node, node(val.first, val.second));
		    		temp->right = new_node;
		    		new_node->parent = temp;
		    		temp = NULL;
		    	}
                else if(temp->right == end_itt.ptr)
		    	{
		    		new_node = Alloc.allocate(1);
                    Alloc.construct(new_node, node(val.first, val.second));
		    		temp->right = new_node;
		    		new_node->parent = temp;
                    new_node->right = end_itt.ptr;
                    (end_itt.ptr)->parent = new_node;
		    		temp = NULL;
		    	}
		    	else
		    		temp = temp->right;
		    }		
		    else if (!Comp(temp->first, val.first))
		    {	
		    	if(temp->left == NULL)
		    	{
		    		new_node = Alloc.allocate(1);
                    Alloc.construct(new_node, node(val.first, val.second));
		    		temp->left = new_node;
		    		new_node->parent = temp;
		    		temp = NULL;
		    	}
                else if(temp->left == rend_itt.ptr)
		    	{
		    		new_node = Alloc.allocate(1);
                    Alloc.construct(new_node, node(val.first, val.second));
		    		temp->left = new_node;
		    		new_node->parent = temp;
                    new_node->left = rend_itt.ptr;
                    (rend_itt.ptr)->parent = new_node;
		    		temp = NULL;
		    	}
		    	else
		    		temp = temp->left;
	    	}
        }
	    repair_tree(new_node);
	    if (new_node->parent == NULL)
	    	head = new_node;
        head = find_head(head);
        Size++;
        begin_itt = find_begin(head);
        return (pair<iterator,bool>(iterator(new_node), true));
    }

    iterator insert (iterator position, const value_type& val)
    {
        node *new_node;
        node *temp;
        
        if ((temp = rb_search(&(val.first))))
            return (iterator(temp));
        if (testHint(position, val) == true)
        {
		    	temp = position.ptr;
                if (temp->right == NULL || temp->right == end_itt.ptr)
                {
                    new_node = Alloc.allocate(1);
                    Alloc.construct(new_node, node(val.first, val.second));
		    		temp->right = new_node;
		    		new_node->parent = temp;
                    if (end_itt.ptr->parent == temp)
                    {
                        new_node->right = end_itt.ptr;
                        end_itt.ptr->parent = new_node;
                    }
                }
                else
                {
                    temp = temp->right;
                    while (temp->left)
                        temp = temp->left;
		    		new_node = Alloc.allocate(1);
                    Alloc.construct(new_node, node(val.first, val.second));
		    		temp->left = new_node;
		    		new_node->parent = temp;
                }
	        repair_tree(new_node);
	        if (new_node->parent == NULL)
	        	head = new_node;
            head = find_head(head);
            Size++;
            begin_itt = find_begin(head);
            return (iterator(new_node));
        }
        else
        {
            ft::pair<iterator,bool> ret = insert(val);
            return (ret.first);
        }
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
            insert(*temp);
            temp++;
        }
    }

    size_type size() const
    {
        return (Size);
    }

    bool empty() const
    {
        return (Size == 0);
    }
    
    size_type max_size() const
    {
        if (INTPTR_MAX == INT32_MAX)
            return (4294967296 / sizeof(s_node<Key,T>));
        std::numeric_limits<size_t> lim; 
        return (lim.max() / sizeof(s_node<const Key,T>)); 
    }

    iterator find (const key_type& keyword)
    {
        node *temp;
        if ((temp = rb_search(&keyword)))
            return (iterator(temp));
        return (end_itt);
    }

    const_iterator find (const key_type& keyword) const
    {
        node *temp;
        if ((temp = rb_search(&keyword)))
            return (const_iterator(temp));
        return (end_itt);
    }

    size_type count (const key_type& keyword) const
    {
        if (rb_search(&keyword))
            return (1);
        return (0);
    }

    mapped_type& operator[] (const key_type& keyword)
    {
        node *temp;
        if ((temp = rb_search(&keyword)))
            return (temp->second);
        pair<iterator, bool> pa = insert(ft::make_pair(keyword, mapped_type()));
        return (pa.first.ptr->second);
    }

    iterator upper_bound (const key_type& keyword)
    {
        iterator temp;

        temp = begin_itt;
        while (temp != end_itt)
        {
            if (Comp(keyword, temp.ptr->first))
                return (temp);
            temp++;
        }
        return (end_itt);
    }

    const_iterator upper_bound (const key_type& keyword) const
    {
        const_iterator temp;
        const_iterator end_const = const_iterator(end_itt);

        temp = begin_itt;
        while (temp != end_const)
        {
            if (Comp(keyword, temp.ptr->first))
                return (temp);
            temp++;
        }
        return (end_itt);
    }

    iterator lower_bound (const key_type& keyword)
    {
        iterator temp;

        temp = begin_itt;
        while (temp != end_itt)
        {
            if (!Comp(temp.ptr->first, keyword))
                return (temp);
            temp++;
        }
        return (end_itt);
    }

    const_iterator lower_bound (const key_type& keyword) const
    {
        const_iterator temp;
        const_iterator end_const = const_iterator(end_itt);

        temp = begin_itt;
        while (temp != end_const)
        {
            if (!Comp(temp.ptr->first, keyword))
                return (temp);
            temp++;
        }
        return (end_itt);
    }
    pair<const_iterator,const_iterator> equal_range (const key_type& keyword) const
    {
        return (ft::make_pair(lower_bound(keyword),upper_bound(keyword)));
    }
    pair<iterator,iterator>             equal_range (const key_type& keyword)
    {
        return (ft::make_pair(lower_bound(keyword),upper_bound(keyword)));
    }

    void clear()
    {
        rb_clear(head);
        begin_itt = end_itt;
        rend_itt = end_itt;
        end_itt.ptr->parent = NULL;
        head = end_itt.ptr;
        Size = 0;
    }

    	
    void erase (iterator position)
    {
        if (position == end_itt || !position.ptr || position == rend_itt)
            return;
        node *todelete = position.ptr;
        rb_delete(todelete);
        if (end_itt.ptr == rend_itt.ptr)
            return;
        Alloc.destroy(todelete);
        Alloc.deallocate(todelete, 1);
        Size--;
        head = find_head(end_itt.ptr);
        begin_itt = find_begin(head);
    }

    size_type erase (const key_type& keyword)
    {
        node *todelete = rb_search(&keyword);
        if (!todelete)
            return (0);
        rb_delete(todelete);
        if (end_itt.ptr == rend_itt.ptr)
            return (1);
        Alloc.destroy(todelete);
        Alloc.deallocate(todelete, 1);
        Size--;
        head = find_head(end_itt.ptr);
        begin_itt = find_begin(head);
        return (1);
    }
    
    void erase (iterator first, iterator last)
    {
        if (first == last)
            return;
        iterator temp = first;
        node *todelete;
        while (temp != last)
        {
            if (temp == end_itt.ptr || temp == rend_itt.ptr)
                return;
            todelete = temp.ptr; 
            temp++;
            rb_delete(todelete);
            if (end_itt.ptr == rend_itt.ptr)
                return;
            Alloc.destroy(todelete);
            Alloc.deallocate(todelete, 1);
            Size--;
            head = find_head(end_itt.ptr);
            begin_itt = find_begin(head);
        }
    }

   key_compare key_comp() const
   {
       return (Comp);
   }

    value_compare value_comp() const
    {
        return (value_compare(Comp));
    }

    void swap (map& x)
    {
        node *head_tp = head;
        iterator begin_itt_tp = begin_itt;
        iterator end_itt_tp = end_itt;
        iterator rend_itt_tp = rend_itt;
        size_type Size_tp = Size;
        head = x.head;
        begin_itt  = x.begin_itt;
        end_itt = x.end_itt;
        rend_itt = x.rend_itt;
        Size = x.Size;
        x.head = head_tp;
        x.begin_itt = begin_itt_tp;
        x.end_itt  = end_itt_tp;
        x.rend_itt = rend_itt_tp;
        x.Size = Size_tp;
    }

    allocator_type get_allocator() const
    {
        return(allocator_type());
    }

private:
    node *head;
    allocator_type Alloc;
    key_compare Comp;
    iterator begin_itt;
    iterator end_itt;
    iterator rend_itt;
    size_type Size;
    
    void    rb_clear(node *nd)
    {
        if (nd->left)
            rb_clear(nd->left);
        if (nd->right && nd->right != end_itt.ptr)
            rb_clear(nd->right);
        if (nd != end_itt.ptr)
        {
            Alloc.destroy(nd);
            Alloc.deallocate(nd, 1);
        }
    }

    node	*rb_search(const Key *keyword) const
    {
    	node	*tmp_node;

    	tmp_node = head;
        if (begin_itt.ptr == end_itt.ptr)
            return (NULL);
    	while (tmp_node)
    	{
    		if (!Comp(tmp_node->first, *keyword) && !Comp(*keyword, tmp_node->first))
    			return (tmp_node);
    		else if (Comp(tmp_node->first, *keyword))
    		{	
    			if(tmp_node->right == NULL || tmp_node->right == end_itt.ptr)
    				return (NULL);
    			else
    				tmp_node = tmp_node->right;
    		}		
    		else
    		{	
    			if(tmp_node->left == NULL || tmp_node->left == rend_itt.ptr)
    				return (NULL);
    			else
    				tmp_node = tmp_node->left;
    		}
    	}
    	return (NULL);
    }

    node *uncle(node *anode)
    {
    	if (anode->parent->parent == NULL)
    		return (NULL);
    	if (anode->parent == anode->parent->parent->left)
    		return (anode->parent->parent->right);
    	else
    		return (anode->parent->parent->left);
    }

    void    repair_tree(node *anode)
    {
    	node *uncle_node;

    	if (anode->parent == NULL)
    	{	
    		anode->color = RB_BLACK;
    		return;
    	}
    	if (anode->parent->color == RB_RED)
    	{
    		uncle_node = uncle(anode);
    		if (uncle_node == NULL || uncle_node == rend_itt.ptr || uncle_node == end_itt.ptr || uncle_node->color == RB_BLACK)
    		{
    			if (anode->parent->parent->left != NULL && anode->parent->parent->left != rend_itt.ptr && anode == anode->parent->parent->left->right)
    			{
    				left_rotation(anode->parent);
    				anode = anode->left;
    			}
    			else if (anode->parent->parent->right != NULL && anode->parent->parent->right != end_itt.ptr && anode == anode->parent->parent->right->left)
    			{	
    				right_rotation(anode->parent);
    				anode = anode->right;
    			}
    			if (anode == anode->parent->left)
    			{	
    				right_rotation(anode->parent->parent);
    				anode->parent->right->color = RB_RED;
    			}
    			else
    			{
    				left_rotation(anode->parent->parent);
    				anode->parent->left->color = RB_RED;
    			}
    			anode->parent->color = RB_BLACK;
    		}
    		else if (uncle_node->color == RB_RED && uncle_node != rend_itt.ptr && uncle_node != end_itt.ptr)
    		{	
    			uncle_node->color = RB_BLACK;
    			anode->parent->color = RB_BLACK;
    			anode->parent->parent->color = RB_RED;
    			repair_tree(anode->parent->parent);
    		}
    	}		
    }
    
    void    rb_replace(node *head, node *toreplace, node *tomove)
    {
        if (head == toreplace)
        {
            head = tomove;
        }
        else if (toreplace == toreplace->parent->left)
        {
            toreplace->parent->left = tomove;
        }
        else
        {
            toreplace->parent->right = tomove;
        }
        if (tomove)
        {
            tomove->parent = toreplace->parent;
            if (toreplace->left && tomove != toreplace->left && tomove != end_itt.ptr && tomove != rend_itt.ptr)
            {
                toreplace->left->parent = tomove;
                tomove->left = toreplace->left;
            }
            if (toreplace->right  && tomove != end_itt.ptr && tomove != rend_itt.ptr && tomove != toreplace->right)
            {
                toreplace->right->parent = tomove;
                tomove->right = toreplace->right;
            }
        }
    }

    void    rb_delete(node *todelete)
    {
        if ((!todelete->left || todelete->left == rend_itt.ptr) && todelete->right && todelete->right != end_itt.ptr)
        {
            if (todelete->color == RB_BLACK)
                todelete->right->color = RB_BLACK;
            rb_replace(head, todelete, todelete->right);
        }
        else if ((!todelete->right || todelete->right == end_itt.ptr) && todelete->left && todelete->left != rend_itt.ptr)
        {   
            if (todelete->color == RB_BLACK)
                todelete->left->color = RB_BLACK;
            rb_replace(head, todelete, todelete->left);
        }
        else if (todelete->right == end_itt.ptr && todelete->left == rend_itt.ptr)
        {
            clear();
        }
        else if ((!todelete->right || todelete->right == end_itt.ptr) && (!todelete->left || todelete->left == rend_itt.ptr))
        {
            if (todelete == todelete->parent->left)
            {
                todelete->parent->left = todelete->left;
                if (todelete->left)
                    todelete->left->parent = todelete->parent;
                if (todelete->color == RB_BLACK)
                    repair_del_tree(todelete->parent,1);
            }
            else if (todelete == todelete->parent->right)
            {
                todelete->parent->right = todelete->right; 
                if (todelete->right)
                    todelete->right->parent = todelete->parent;
                if (todelete->color == RB_BLACK)
                    repair_del_tree(todelete->parent,2);
            }
        }
        else
        {
            node *temp = todelete->right;
            while (temp->left)
            {
                temp = temp->left;
            }
            node *test = temp->right;
            if (temp->color == RB_BLACK && (!test || test == end_itt.ptr || test == rend_itt.ptr))
            {
                temp = todelete->left;
                while (temp->right)
                {
                    temp = temp->right;
                }
                test = temp->left;
                enum e_rb_color color_tp = temp->color;
                if (temp->parent != todelete)
                {
                    node *torep = temp->parent;
                    rb_replace(head, temp, temp->left);
                    rb_replace(head, todelete, temp);
                    temp->color = todelete->color;
                    if (color_tp == RB_BLACK && (!test || test == end_itt.ptr || test == rend_itt.ptr))
                    {
                        repair_del_tree(torep,2);
                    }
                    else if (color_tp == RB_BLACK && test && test != end_itt.ptr && test != rend_itt.ptr)
                        test->color = RB_BLACK;
                }    
                else
                {
                    rb_replace(head, todelete, temp);
                    temp->color = todelete->color;
                    if (color_tp == RB_BLACK && (!test || test == end_itt.ptr || test == rend_itt.ptr))
                    {
                        repair_del_tree(temp, 1);
                    }
                    else if (color_tp == RB_BLACK && test && test != end_itt.ptr && test != rend_itt.ptr)
                        test->color = RB_BLACK;
                }
            }
            else
            {
                if (temp->parent != todelete)
                {
                    rb_replace(head, temp, temp->right);
                    temp->right = todelete->right;
                    temp->right->parent = temp;
                }    
                rb_replace(head, todelete, temp);
                temp->left = todelete->left;
                temp->left->parent = temp;
                temp->color = todelete->color;
                if (test && test != end_itt.ptr && test != rend_itt.ptr)
                    test->color = RB_BLACK;
            }
        }
    }

    void    repair_del_tree(node *torep, int dir) // dir : 1 = left 2 = right
    {
        node *P;
        node *S;
        if (dir == 1)
        {
            P = torep;   // parent of deleted node
            S = P->right; // sibling of deleted node
            node *D = S->right; // distant nephew of deleted node
            node *C = S->left; // close nephew of deleted node
            if (S->color == RB_RED)	    	
            {
                left_rotation(P);
                P->color = RB_RED;
                S->color = RB_BLACK;
                S = C;
                D = S->right;
                C = S->left; 
            }
            if (C && C != end_itt.ptr && C != rend_itt.ptr && C->color == RB_RED)
            {
                right_rotation(S);
                S->color = RB_RED;
                C->color = RB_BLACK;
                D = S;
                S = C;
            }
            if (D && D != end_itt.ptr && D != rend_itt.ptr && D->color == RB_RED)
            {
                left_rotation(P);
                S->color = P->color;
                P->color = RB_BLACK;
                D->color = RB_BLACK;
                return;
            }
            if (P->color == RB_RED)
            {
                S->color = RB_RED;
                P->color = RB_BLACK;
                return;
            }
        }
        else
        {
            P = torep;   // parent of deleted node
            S = P->left; // sibling of deleted node
            node *D = S->left; // distant nephew of deleted node
            node *C = S->right; // close nephew of deleted node
            if (S->color == RB_RED)
            {
                right_rotation(P);
                P->color = RB_RED;
                S->color = RB_BLACK;
                S = C;
                D = S->left;
                C = S->right;
            }
            if (C && C != end_itt.ptr && C != rend_itt.ptr && C->color == RB_RED)
            {
                left_rotation(S);
                S->color = RB_RED;
                C->color = RB_BLACK;
                D = S;
                S = C;
            }
            if (D && D != end_itt.ptr && D != rend_itt.ptr && D->color == RB_RED)
            {
                right_rotation(P);
                S->color = P->color;
                P->color = RB_BLACK;
                D->color = RB_BLACK;
                return;
            }
            if (P->color == RB_RED)
            {
                S->color = RB_RED;
                P->color = RB_BLACK;
                return;
            }
        }
        S->color = RB_RED;
        if (P->parent && (P == P->parent->right))
            repair_del_tree(P->parent, 2);
        else if (P->parent && (P == P->parent->left))
            repair_del_tree(P->parent, 1);
    }
    
    void 	left_rotation(node	*anode)
    {
    	node	*tmp_node;

    	tmp_node = anode->right;
    	anode->right = tmp_node->left;
    	if (anode->right != 0)
    		anode->right->parent = anode;
    	tmp_node->parent = anode->parent;
    	if (tmp_node->parent != 0)
    	{
    		if (anode == tmp_node->parent->left)
    			tmp_node->parent->left = tmp_node;
    		else
    			tmp_node->parent->right = tmp_node;
    	}
    	tmp_node->left = anode;
    	anode->parent = tmp_node;
        head = find_head(anode);
    }

    void	right_rotation(node *anode)
    {
    	node	*tmp_node;

    	tmp_node = anode->left;
    	anode->left = tmp_node->right;
    	if (anode->left != 0)
    		anode->left->parent = anode;
    	tmp_node->parent = anode->parent;
    	if (tmp_node->parent != 0)
    	{
    		if (anode == tmp_node->parent->left)
    			tmp_node->parent->left = tmp_node;
    		else
    			tmp_node->parent->right = tmp_node;
    	}
    	tmp_node->right = anode;
    	anode->parent = tmp_node;
        head = find_head(anode);
    }
    

    bool    testHint(iterator position, const value_type& val)
    {
        if (position.ptr == end_itt.ptr || position.ptr == rend_itt.ptr)
            return false;
        if (Comp(position.ptr->first,val.first))
        {
            iterator temp = position;
            temp++;
            if (Comp(val.first,temp.ptr->first))
                return true;
        }
        return false;
    }

    iterator find_begin(node* head)
    {
        if (head == end_itt.ptr && head == rend_itt.ptr)
            return (head);
        node *temp;
        temp = head;
        while (temp->left && temp->left != rend_itt.ptr)
            temp = temp->left;
        rend_itt.ptr->parent = temp;
        temp->left = rend_itt.ptr;
        if (rend_itt.ptr->right)
		{
            rb_replace(head, rend_itt.ptr, rend_itt.ptr->right);
            return (find_begin(head));
		}
        return (iterator(temp));
    }
    
    node *find_head(node* nd)
    {
        while (nd->parent != NULL)
            nd = nd->parent;
        return (nd);
    }
    
};

template <typename K, typename T, typename C, typename A>
bool operator== (const map<K,T,C,A>& lhs, const map<K,T,C,A>& rhs)
{
    
    if ((lhs.size() == rhs.size()) && ft::equal(lhs.begin(), lhs.end(), rhs.begin()))
        return true;
    return false;
}

template <typename K, typename T, typename C, typename A>
bool operator!= (const map<K,T,C,A>& lhs, const map<K,T,C,A>& rhs)
{
    return (!(lhs == rhs));
}

template <typename K, typename T, typename C, typename A>
bool operator<  (const map<K,T,C,A>& lhs, const map<K,T,C,A>& rhs)
{
    return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <typename K, typename T, typename C, typename A>
bool operator<= (const map<K,T,C,A>& lhs, const map<K,T,C,A>& rhs)
{
    if ((lhs == rhs) || (lhs < rhs))
        return true;
    return false;
}

template <typename K, typename T, typename C, typename A>
bool operator>  (const map<K,T,C,A>& lhs, const map<K,T,C,A>& rhs)
{
    return (!(lhs <= rhs));
}

template <typename K, typename T, typename C, typename A>
bool operator>= (const map<K,T,C,A>& lhs, const map<K,T,C,A>& rhs)
{
    return (!(lhs < rhs));
}

template <typename K, typename T, typename C, typename A>
void swap (map<K,T,C,A>& x, map<K,T,C,A>& y)
{
    x.swap(y);
}

}
#endif
