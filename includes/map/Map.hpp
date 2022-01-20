#ifndef MAP_HPP
# define MAP_HPP

# include <iostream>
# include <string>
# include <memory>
# include <map>
# include "Pair.hpp"
# include "Tree.hpp"
# include "../Iterator/tree_iterator.hpp"
# include "../Iterator/Reverse_iterator.hpp"
# include "../utils.hpp"

namespace ft
{
    template <class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<ft::pair<const Key, T> > >
	class map
	{
        typedef Key 											key_type;
		typedef T 												mapped_type;
		typedef ft::pair<const Key, T> 							value_type;
		typedef Compare 										key_compare;
		typedef Alloc 											allocator_type;
		typedef typename allocator_type::reference 				reference;
		typedef typename allocator_type::const_reference 		const_reference;
		typedef typename allocator_type::pointer 				pointer;
		typedef typename allocator_type::const_pointer 			const_pointer;
		typedef typename allocator_type::size_type				size_type;
		typedef typename allocator_type::difference_type		difference_type;
		
	private:
		typedef RBtree<value_type, key_compare, allocator_type> 				tree;
		typedef ft::Node<value_type>											Node;
		typedef Node*															node_ptr;
		typedef RBtree<const value_type, key_compare, allocator_type>			const_tree;
		
	public:
		typedef typename tree::value_compare								value_compare;

		typedef TreeIterator<bidirectional_iterator_tag, tree> 				iterator;
		typedef TreeIterator<bidirectional_iterator_tag, const_tree, tree>	const_iterator;

		typedef ft::reverse_iterator<iterator> 						reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> 				const_reverse_iterator;

    explicit map(const Compare& comp = key_compare(), const allocator_type &alloc = allocator_type()): _tree(comp, alloc){
    }

    template<class InputIterator>
    map(InputIterator first, InputIterator last, const Compare& comp = key_compare(), const allocator_type &alloc = allocator_type()): _tree(comp, alloc){
        this->insert(first, last);
    }

    map(const map& origin){
        this->_tree = origin._tree;
    }

    map& operator=(const map& origin){
        this->_tree = origin._tree;
        return (*this);
    }

    ~map(){
    }

    iterator begin(){
        return(iterator(this->_tree.begin_node(), this->_tree.getRoot()));
    }

    const_iterator begin()const{
        return(const_iterator(this->_tree.begin_node(), this->_tree.getRoot()));
    }

    iterator end(){
        return(iterator(this->_tree.end_node(), this->_tree.getRoot()));
    }

    const_iterator end()const{
        return(const_iterator(this->_tree.end_node(), this->_tree.getRoot()));
    }

    reverse_iterator rbegin(){
        return(reverse_iterator(this->_tree.begin_node(), this->_tree.getRoot()));
    }

    const_reverse_iterator rbegin()const{
        return(const_reverse_iterator(this->_tree.begin_node(), this->_tree.getRoot()));
    }

    reverse_iterator rend(){
        return(reverse_iterator(this->_tree.end_node(), this->_tree.getRoot()));
    }

    const_reverse_iterator rend()const{
        return(const_reverse_iterator(this->_tree.end_node(), this->_tree.getRoot()));
    }

    bool empty() const {
        return(this->size() == 0);
    }

    size_type size()const {
        return (this->_tree.size());
    }

    size_type max_size()const{
        return (this->_tree.max_size());
    }

    mapped_type& operator[](const key_type &key){
        return (this->_tree[key]);
    }

    ft::pair<iterator, bool> insert(const value_type& val){
       ft::pair<node_ptr, bool>tmp = this->_tree.insert_single_elem(val);
       ft::pair<iterator, bool>res(iterator(tmp.first, this->_tree.getRoot()), tmp.second); 
    }

    iterator insert(iterator hint, const value_type& value){
        (void)hint;
        node_ptr tmp = this->_tree.searchTree(value);
        if (!tmp->is_tnull())
            return(iterator(tmp, this->_tree.getRoot()));
        return (this->insert(value).first);
    }

    template<class InputIterator>
    void insert(InputIterator first, InputIterator last){
        while (first != last)
        {
            this->_tree.insert(*first);
            first++;
        }
    }

    void erase (iterator position) {
        this->erase(position->first);
    } 

    size_type erase(const key_type& key){
        size_type check = this->size();
        this->_tree.deleteNodeKey(key);
        return (check != this->size());
    }

    void erase(iterator first, iterator last){
        iterator tmp;
        while (first != last){
            tmp = first;
            ++first;
            this->_tree.erase(tmp);
        }
    }

    void swap(map &x){
        this->_tree.swap(x._tree);
    }

    void clear(){
        this->_tree.clear();
    }

    key_compare key_comp() const {
        return (this->_tree.get_key_comp());
    }

    value_compare value_comp() const {
        return (this->_tree.get_value_comp());
    }

    iterator find (const key_type& k){
		node_ptr node = this->_tree.searchTreeKey(k);
		if (node->is_tnull())
			return (this->end());
		return (iterator(node, this->_tree.getRoot()));
	}

    const_iterator find (const key_type& k) const{
		node_ptr node = this->_tree.searchTreeKey(k);
		if (node->is_tnull())
			return (this->end());
		return (const_iterator(node, this->_tree.getRoot()));
	}

    iterator upper_bound (const key_type& k){
		return (iterator(this->_tree.upper_bound(k), this->_tree.getRoot() ));
	}

	const_iterator upper_bound (const key_type& k) const{
		return (const_iterator(this->_tree.upper_bound(k), this->_tree.getRoot() ));
	}

    pair<iterator,iterator>	equal_range (const key_type& k){
		return (pair<iterator, iterator>(this->lower_bound(k), this->upper_bound(k)));
	}
		
	pair<const_iterator, const_iterator>	equal_range (const key_type& k) const{
		return (pair<const_iterator, const_iterator>(this->lower_bound(k), this->upper_bound(k)));
	}

    allocator_type get_allocator()const{
        return (allocator_type(this->_tree.get_allocator()));
    }

    RBtree<value_type, Compare, Alloc>	&getTree(){
         return _tree;
    }

    private:
		RBtree<value_type, Compare, Alloc>	_tree;
    };

    	template <class Key, class T, class Compare, class Alloc>
	bool operator== ( const ft::map<Key,T,Compare,Alloc>& first, const ft::map<Key,T,Compare,Alloc>& second ){
		if (first.size() != second.size())
			return (0);
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it = first.begin();
		typename ft::map<Key, T, Compare, Alloc>::const_iterator it2 = second.begin();
		while (it != first.end())
		{
			if (*it != *it2)
				return (0);
			it++;
			it2++;
		}
		return (1);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator!= ( const ft::map<Key, T, Compare, Alloc>& first, const ft::map<Key, T, Compare, Alloc>& second ) {
		return !(first == second);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<  ( const ft::map<Key, T, Compare, Alloc>& first, const ft::map<Key, T, Compare, Alloc>& second ){
		return (ft::lexicographical_compare(first.begin(), first.end(), second.begin(), second.end()));
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator<= ( const ft::map<Key, T, Compare, Alloc>& first, const ft::map<Key, T, Compare, Alloc>& second ){
		return !(second < first);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>  ( const ft::map<Key, T, Compare, Alloc>& first, const ft::map<Key, T, Compare, Alloc>& second ){
		return (second < first);
	}

	template <class Key, class T, class Compare, class Alloc>
	bool operator>= ( const ft::map<Key, T, Compare, Alloc>& lhs, const ft::map<Key, T, Compare, Alloc>& second ){
		return !(lhs < second);
	}

	template< class Key, class T, class Compare, class Alloc >
	void swap( ft::map<Key, T, Compare, Alloc>& lhs, ft::map<Key, T, Compare, Alloc>& second ){
		lhs.swap(second);
	}
}
#endif