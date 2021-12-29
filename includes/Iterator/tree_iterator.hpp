/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jehaenec <jehaenec@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 14:16:53 by jehaenec          #+#    #+#             */
/*   Updated: 2021/12/29 17:11:30 by jehaenec         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TREE_ITERATOR_HPP
# define TREE_ITERATOR_HPP

# include "Iterator.hpp"
# include <memory>
# include <string>
# include <iostream>
# include "../map/Node.hpp"
# include "../map/Tree.hpp"

namespace ft
{
  template< class T, class Tree, class not_const_tree = Tree >
  class TreeIterator  : public ft::Iterator< T, Tree >
  {
    public:
        	typedef typename Tree::value_type					value_type;
			typedef typename Tree::key_type						key_type;
			typedef typename Tree::mapped_type					mapped_type;
			typedef	typename Tree::key_compare					key_compare;

			typedef	typename not_const_Tree::Node				Node;

			typedef typename Tree::reference					reference;
			typedef const value_type&							const_reference;
			typedef	typename Tree::pointer						pointer;
			typedef	const value_type*							const_pointer;
        
        TreeIterator(){
            this->_node_ptr = nullptr;
            this->_root = nullptr;
        }

        TreeIterator(Node* node, Node* root){
            this->_node_ptr = node;
            this->_root = root;
        }

        TreeIterator(const TreeIterator & origin){
            this->_node_ptr = origin.getNode();
            this->_root = origin.getRoot();
        }
        
        TreeIterator& operator=(const TreeIterator & origin){
            this->_node_ptr = origin.getNode();
            this->_root = origin.getRoot();
            return (*this);
        }
        
        virtual ~TreeIterator(){
        }
        
        reference operator*(){
            return (this->_node_ptr->data);
        }
        pointer operator->(){
            return (&this->node_ptr->data);
        }
        
        TreeIterator& operator++(){
            this->_node_ptr = forward(this->_node_ptr);
            return (this->_node_ptr);
        }
        
        TreeIterator operator++(int){
            Node tmp_node = this->_node_ptr;
            forward(this->_node_ptr);
            return (tmp_node);
        }

        TreeIterator& operator--(){
            this->_node_ptr = backward(this->_node_ptr);
            return (this->_node_ptr);
        }
        
        TreeIterator operator--(int){
            Node tmp_node = this->_node_ptr;
            backward(this->_node_ptr);
            return (tmp_node);
        }

        friend bool operator!=(const TreeIterator& a, const TreeIterator& b){
            return (a.getNode() != b.getNode());
        }

        friend bool operator==(const TreeIterator& a, const TreeIterator& b){
             return (a.getNode() == b.getNode());
        }

        friend bool operator<=(const TreeIterator& a, const TreeIterator& b){
             return (a.getNode() <= b.getNode());
        }

        friend bool operator>=(const TreeIterator& a, const TreeIterator& b){
             return (a.getNode() >= b.getNode());
        }
        
        friend bool operator<(const TreeIterator& a, const TreeIterator& b){
             return (a.getNode() < b.getNode());
        }
        
        friend bool operator>(const TreeIterator& a, const TreeIterator& b){
             return (a.getNode() > b.getNode());
        }

        Node * getNode()const{
            return (this->_node_ptr);
        }

        Node * getRoot()const{
            return (this->_root);
        }
        
        Node * forward(Node * cursor){
            if (cursor && cursor.right_child && !(cursor.right_child.is_tnull()))
                return (cursor->right_child.down_left());
            else
            {
                Node *ref_to_tnull = cursor->right_child;
                Node *p = cursor->parent;
                while (p && !p->is_tnull() && cursor == p->right_child)
                {
                    cursor = p;
                    p = p->parent;
                }
                cursor = p;
                if (cursor == nullptr)
                    return (ref_to_null);
            }
            return (cursor);
        }

        Node * backward(Node * cursor){
            if (cursor->is_tnull())
            {
                if (!(this->_root->is_tnull())
                    return (this->_root->down_right());
                return (cursor);
            }
            if (cursor && cursor->left_child && !(cursor->left_child.is_tnull()))
                return (cursor->left_child->down_right());
            else
            {
                Node *ref_to_tnull = cursor->left_child;
                Node *p = cursor->parent;
                while (p && !p->is_tnull() && cursor == p->left_child)
                {
                    cursor = p;
                    p = p->parent;
                }
                cursor = p;
                if (cursor == nullptr)
                    return (ref_to_null);
            }
            return (cursor);
        }
              
    private:
            Node *_node_ptr;
            Node *_root;
  }; 
    
}

#endif