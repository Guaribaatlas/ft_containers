#ifndef NODE_HPP
# define NODE_HPP

#include <iostream>
#include <string>

namespace ft
{
    template <class T>
    struct Node
    {
        typedef T value_type;
        value_type data;
        Node    *parent;
		Node	*left_child;
		Node	*right_child;
		bool	color;
		bool	check;

		Node(const value_type& val) : data(val) {}

		Node* down_left(){
			Node *where = this;
			if (where->is_null())
				return (nullptr);
			while (where->left_child && !(where->left_child->is_null()))
				where = where->left_child;
			return (where);
		}

		Node* down_right(){
			Node *where = this;
			if (where->is_null())
				return (nullptr);
			while (where->right_child && !(where->right_child->is_null()))
				where = where->right_child;
			return (where);			
		}

		Node* get_top(){
			Node *where = this;
			if (where->is_null())
				return (nullptr);
			while(!(where->parent->is_null()))
				where = where->parent;
			return where;
		}

		bool get_color(){
			return (this->color);
		}

		Node* get_parent(){
			Node *where = this;
			if (where->is_null() || where->parent->is_null())
				return (nullptr);
			return (where->parent);
		}
		bool is_null(){
			return (check);
		}
    };
};

#endif