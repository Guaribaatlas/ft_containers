#ifndef TREE_HPP
#define TREE_HPP

#include "Node.hpp"
#include "Pair.hpp"
#include <string>

namespace ft
{
    template<class T, class compare = std::less<typename T::first_type>, class Alloc = std::allocator<T> >
    class RBtree
    {
        public:
            typedef T   value_type;
            typedef ft::Node<value_type> Node;
            typedef size_t  size_type;
            typedef Alloc   allocator_type;

            typedef typename allocator_type::difference_type difference_type;
			typedef typename std::bidirectional_iterator_tag iterator_category;
            typedef typename T::first_type key_type;
            typedef typename T::second_type mapped_type;
            typedef typename T::second_type pair;

            typedef compare key_compare;
            typedef value_type& reference;
            typedef const value_type&			const_reference;
		    typedef	value_type*					pointer;
		    typedef	const value_type*			const_pointer;

		    typedef Node*						node_ptr;
		    typedef const Node*					const_node_ptr;

        private:
            typename allocator_type::template rebind<Node>::other	_node_alloc;
		    allocator_type											_alloc;
		    node_ptr												_root;
		    node_ptr												_tnull;
		    key_compare												_comp;

        public:
            class value_compare : public std::binary_function<value_type, value_type, bool>
            {
                class RBTree;
                private:
                    key_compare comp;
                public:
                    value_compare(const key_compare &x): comp(x){
                    }
                    bool operator()(const value_type&x, const value_type &y) const{
                        return (comp(x.first, y.first));
                    }
            };
        public:
            RBtree(const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()):_alloc(alloc), _comp(comp){
				
                _tnull = _node_alloc.allocate(1);
                _tnull->check = 1;
                _tnull->color = 0;
                _tnull->left_child = nullptr;
                _tnull->right_child = nullptr;
                this->_root = _tnull;
            }

            RBtree(const RBtree& origin){
                this->_alloc = origin._alloc;
                this->_comp = origin._comp;
                this->_node_alloc = origin._node_alloc;

                _tnull = _node_alloc.allocate(1);
                _tnull->check = 1;
                _tnull->color = 0;
                _tnull->left_child = nullptr;
                _tnull->right_child = nullptr;
                this->_root = _tnull;
                this->_root = this->copy_tree(nullptr, this->_root, origin._root);
            }

            RBtree& operator=(const RBtree &origin){
                this->clear();
                this->_alloc = origin._alloc;
                this->_node_alloc = origin._node_alloc;
                this->_comp = origin._comp;
                this->_root = _tnull;
                this->_root = this->copy_tree(nullptr, this->_root, origin._root);
				return (*this);
            }

            node_ptr copy_tree(node_ptr parent, node_ptr node, const node_ptr ref){
                if (ref && !ref->check)
                {
                    node = copy_node(parent, node,  ref);
                    if (ref->left_child && !ref->left_child->check)
                        node->left_child = copy_tree(node, node->left_child, ref->left_child);
                    if (ref->right_child && !ref->right_child->check)
                        node->right_child = copy_tree(node, node->right_child, ref->right_child); 
                }
                return (node);
            }

            node_ptr copy_node(node_ptr parent, node_ptr node, const node_ptr ref){
                node = this->_node_alloc.allocate(1);
                node->parent = parent;
                node->check = 0;
                node->left_child = this->_tnull;
                node->right_child = this->_tnull;
                node->color = ref->color;
                this->_alloc.construct(&node->data, ref->data);
                return (node);
            }

            ~RBtree(){
                this->clear();
                this->_node_alloc.deallocate(this->_tnull, 1);
            }

            void clear(){
				
                this->destroy_tree(this->_root);
                this->_root = this->_tnull;
            }

            void destroy_tree(node_ptr node){
                if (node && !(node->check))
				{
					if (node->left_child && !node->left_child->check)
                	    destroy_tree(node->left_child);
                	if (node && !(node->right_child))
                    	destroy_tree(node->right_child);
                	this->_alloc.destroy(&node->data);
                	this->_node_alloc.deallocate(node, 1);
				}
            }

            node_ptr begin_node() const{
                if (this->_root && !(this->_root == this->_tnull))
                    return (this->minimum(this->_root));
                return (this->_tnull);          
            }

            node_ptr end_node() const{
                return (this->_tnull);
            }

            void preorder(){
			    preOrderHelper(this->_root);
		    }

            void inorder(){
			    inOrderHelper(this->_root);
		    }

            void postorder(){
			    postOrderHelper(this->_root);
		    }
	
		    node_ptr searchTree(value_type k){
			    return searchTreeHelper(this->_root, k);
		    }
            
            node_ptr minimum(node_ptr node) const{
			    while (node->left_child != _tnull)
				    node = node->left_child;
			    return node;
		    }

            node_ptr maximum(node_ptr node) const{
			    while (node->right_child != _tnull)
				    node = node->right_child;
			    return node;
		    }

            node_ptr successor(node_ptr x){
                if (x->right_child != _tnull)
				    return minimum(x->right_child);
                node_ptr y = x->parent;
			    while (y != _tnull && x == y->right_child)
			    {
				    x = y;
				    y = y->parent;
			    }
			    return y;
            }

            node_ptr predecessor(node_ptr x){
                if (x->left_child != _tnull)
				    return maximum(x->left_child);
                node_ptr y = x->parent;
			    while (y != _tnull && x == y->left_child)
			    {
				    x = y;
				    y = y->parent;
			    }
                return (y);
            }

            void leftRotate(node_ptr x)
		    {
			    node_ptr y = x->right_child;
			        x->right_child = y->left_child;
			    if (y->left_child != _tnull)
				    y->left_child->parent = x;
			    y->parent = x->parent;
			    if (x->parent == nullptr)
				this->_root = y;
			    else if (x == x->parent->left_child)
				    x->parent->left_child = y;
			    else
				    x->parent->right_child = y;
			    y->left_child = x;
			    x->parent = y;
            }

            void rightRotate(node_ptr x)
		    {
			    node_ptr y = x->left_child;
			    x->left_child = y->right_child;
			    if (y->right_child != _tnull)
				    y->right_child->parent = x;
			    y->parent = x->parent;
			    if (x->parent == nullptr)
				    this->_root = y;
			    else if (x == x->parent->right_child)
				    x->parent->right_child = y;
			    else
				x->parent->left_child = y;
			    y->right_child = x;
			    x->parent = y;
		    }

            node_ptr insert(const value_type & key)
		    {
			    node_ptr tmp = searchTree(key);
			    if (tmp != _tnull)
				    return tmp;
			    node_ptr node = _node_alloc.allocate(1);
			    node->parent = nullptr;
			    node->check = 0;
			    this->_alloc.construct(&node->data, key);
			    node->left_child = _tnull;
			    node->right_child = _tnull;
			    node->color = 1;
			    node_ptr y = nullptr;
			    node_ptr x = this->_root;
			    while (x != _tnull)
			    {
				    y = x;
				    if (this->_comp(node->data.first, x->data.first))
					    x = x->left_child;
				    else
					    x = x->right_child;
			    }
			    node->parent =  y;
			    if (y == nullptr)
				    _root = node;
			    else if (this->_comp(node->data.first, y->data.first))
				    y->left_child = node;
			    else
				y->right_child = node;
			    if (node->parent == nullptr)
			    {
				    node->color = 0;
				    return node;
			    }
			    if (node->parent->parent == nullptr)
				    return node;
			    fixInsert(node);
			    return node;
		}

        ft::pair<node_ptr, bool> insert_single_elem(const value_type & key){
			node_ptr tmp = searchTreeKey(key.first);
			if (tmp != _tnull)
			{
				ft::pair<node_ptr, bool> res_pair(tmp, false);
				return (res_pair);
			}
			else
			{
				tmp = insert(key);
				ft::pair<node_ptr, bool> res_pair(tmp, true);
				return (res_pair);
			}
		}

        node_ptr getRoot() const{
			return this->_root;
		}

		void deleteNode(value_type data){
			deleteNodeHelper(this->_root, data);
		}

		void prettyPrint(){
			if (_root)
				printHelper(this->_root, "", true);
		}

        private:

		void initializeNULLNode(node_ptr node, node_ptr parent)
		{
			node->data = 0; 
			node->parent = parent;
			node->left_child = nullptr;
			node->right_child = nullptr;
			node->color = 0;
		}

		void preOrderHelper(node_ptr node)
		{
			if (node != _tnull)
			{
				std::cout << node->data << " ";
				preOrderHelper(node->left_child);
				preOrderHelper(node->right_child);
			}
		}

		void inOrderHelper(node_ptr node)
		{
			if (node != _tnull)
			{
				inOrderHelper(node->left_child);
				std::cout << node->data << " ";
				inOrderHelper(node->right_child);
			}
		}

		void postOrderHelper(node_ptr node)
		{
			if (node != _tnull)
			{
				postOrderHelper(node->left_child);
				postOrderHelper(node->right_child);
				std::cout << node->data << " ";
			}
		}

		node_ptr searchTreeHelper(node_ptr node, value_type key)
		{
			if (node == _tnull || (!this->_comp(key.first, node->data.first) && !this->_comp(node->data.first, key.first)))
				return node;
			if (this->_comp(key.first, node->data.first))
				return searchTreeHelper(node->left_child, key);
			return searchTreeHelper(node->right_child, key);
		}

        void fixDelete(node_ptr x)
		{
			node_ptr s;
			while (x != _root && x->color == 0)
			{
				if (x == x->parent->left_child)
				{
					s = x->parent->right_child;
					if (s->color == 1)
					{
						s->color = 0;
						x->parent->color = 1;
						leftRotate(x->parent);
						s = x->parent->right_child;
					}

					if (s->left_child->color == 0 && s->right_child->color == 0)
					{
						s->color = 1;
						x = x->parent;
					}
					else
					{
						if (s->right_child->color == 0)
						{
							s->left_child->color = 0;
							s->color = 1;
							rightRotate(s);
							s = x->parent->right_child;
						}
						s->color = x->parent->color;
						x->parent->color = 0;
						s->right_child->color = 0;
						leftRotate(x->parent);
						x = _root;
					}
				}
				else
				{
					s = x->parent->left_child;
					if (s->color == 1)
					{
						s->color = 0;
						x->parent->color = 1;
						rightRotate(x->parent);
						s = x->parent->left_child;
					}

					if (s->right_child->color == 0 && s->right_child->color == 0)
					{
						s->color = 1;
						x = x->parent;
					}
					else
					{
						if (s->left_child->color == 0)
						{
							s->right_child->color = 0;
							s->color = 1;
							leftRotate(s);
							s = x->parent->left_child;
						}
						s->color = x->parent->color;
						x->parent->color = 0;
						s->left_child->color = 0;
						rightRotate(x->parent);
						x = _root;
					}
				}
			}
			x->color = 0;
		}

        void rbTransplant(node_ptr u, node_ptr v)
		{
			if (u->parent == nullptr)
				_root = v;
			else if (u == u->parent->left_child)
				u->parent->left_child = v;
			else
				u->parent->right_child = v;
			v->parent = u->parent;
		}

		bool deleteNodeHelper(node_ptr node, value_type key)
		{
			node_ptr z = _tnull;
			node_ptr x, y;
			while (node != _tnull)
			{
				if (node->data == key)
					z = node;
				if (node->data <= key)
					node = node->right_child;
				else
					node = node->left_child;
			}

			if (z == _tnull)
				return (false);
			y = z;
			int y_original_color = y->color;
			if (z->left_child == _tnull)
			{
				x = z->right_child;
				rbTransplant(z, z->right_child);
			}
			else if (z->right_child == _tnull)
			{
				x = z->left_child;
				rbTransplant(z, z->left_child);
			}
			else
			{
				y = minimum(z->right_child);
				y_original_color = y->color;
				x = y->right_child;
				if (y->parent == z)
					x->parent = y;
				else
				{
					rbTransplant(y, y->right_child);
					y->right_child = z->right_child;
					y->right_child->parent = y;
				}

				rbTransplant(z, y);
				y->left_child = z->left_child;
				y->left_child->parent = y;
				y->color = z->color;
            }
			_alloc.destroy(&z->data);	
			_node_alloc.deallocate(z, 1);
			
			if (y_original_color == 0)
				fixDelete(x);
			return (true);
		}

        void fixInsert(node_ptr k)
		{
			node_ptr u;
			while (k->parent->color == 1)
			{
				if (k->parent == k->parent->parent->right_child)
				{
					u = k->parent->parent->left_child; 
					if (u->color == 1)
					{
						u->color = 0;
						k->parent->color = 0;
						k->parent->parent->color = 1;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->left_child)
						{
							k = k->parent;
							rightRotate(k);
						}
						k->parent->color = 0;
						k->parent->parent->color = 1;
						leftRotate(k->parent->parent);
					}
				}
				else
				{
					u = k->parent->parent->right_child;
					if (u->color == 1)
					{
						u->color = 0;
						k->parent->color = 0;
						k->parent->parent->color = 1;
						k = k->parent->parent;
					}
					else
					{
						if (k == k->parent->right_child)
						{
							k = k->parent;
							leftRotate(k);
						}
						k->parent->color = 0;
						k->parent->parent->color = 1;
						rightRotate(k->parent->parent);
					}
				}
				if (k == _root)
					break;
			}
			_root->color = 0;
		}

		void printHelper(node_ptr root, std::string indent, bool last)
		{
			if (root != _tnull)
			{
				std::cout << indent;
				if (last)
				{
					std::cout << "R----";
					indent += "     ";
				}
				else
				{
					std::cout << "L----";
					indent += "|    ";
				}

				std::string sColor = root->color ? "RED" : "BLACK";
				std::cout << root->data.first << "," << root->data.second << "(" << sColor << ")" << std::endl;
				printHelper(root->left_child, indent, false);
				printHelper(root->right_child, indent, true);
			}
		}
		
		public :
			node_ptr searchTreeKey(key_type  k) const {
				return searchTreeHelperKey(this->_root, k);
			}

		private:
			node_ptr searchTreeHelperKey(node_ptr node, key_type key) const{
				if (node == _tnull || key == node->data.first)
					return node;
				if (this->_comp(key, node->data.first))
					return searchTreeHelperKey(node->left_child, key);
				return searchTreeHelperKey(node->right_child, key);
			}

		public:
			size_type deleteNodeKey(key_type key)
            {
				node_ptr node = searchTreeKey(key);
				return (deleteNodeHelper(this->_root, node->data));
			}

		public:
			void insertAt(key_type key, mapped_type value)
			{
				node_ptr node = searchTreeKey(key);
				if (node == _tnull)
				{
					value_type p(key, value);
					this->insert(p);
					return ;
				}
				node->data.second = value;
			}

		public:
		mapped_type& 	operator[](const key_type& key) {
			node_ptr node = this->searchTreeKey(key);
			if (node != _tnull)
				return node->data.second;
			this->insert(ft::make_pair<const key_type, mapped_type>(key, mapped_type()));
			return (*this)[key];
		}

		public:
		size_type 	max_size() const {
			size_type test;
			test = this->_node_alloc.max_size();
			if (test == 384307168202282325)
				return 461168601842738790;
			return this->_node_alloc.max_size();
		}

		public:
		size_type 	size() const {
			return (sizeCalc(this->getRoot()));
		}

		size_type	sizeCalc(node_ptr node) const {
			size_type s = 0;
			if (node != _tnull)
			{
				s += sizeCalc(node->left_child);
				s += sizeCalc(node->right_child);
				s++;
			}
			return s;
		}

		public:

		void 	swap(RBtree &x) {
			node_ptr temp = this->_root;
			this->_root = x._root;
			x._root = temp;
			temp = this->_tnull;
			this->_tnull = x._tnull;
			x._tnull = temp;
		}

		public:
		key_compare 	get_key_comp() const {
			return (this->_comp);
		}

		public:
		value_compare 	get_value_comp() const {
			return (value_compare(this->_comp));
		}

		node_ptr lower_bound (const key_type& k) const
		{
			node_ptr cursor = this->_root;
			node_ptr res = this->_tnull;
			while (cursor != _tnull)
			{
				if (this->_comp(cursor->data.first, k) == false)
				{
					res = cursor;
					cursor = cursor->left_child;
				}
				else
					cursor = cursor->right_child;
			}
			return (res);
		}

		node_ptr upper_bound (const key_type& k) const
		{
			node_ptr cursor = this->_root;
			node_ptr res = this->_tnull;
			while (cursor != _tnull)
			{
				if (this->_comp(k, cursor->data.first))
				{
					res = cursor;
					cursor = cursor->left_child;
				}
				else
					cursor = cursor->right_child;
			}
			return (res);
		}

		allocator_type get_allocator() const { 
			return (this->_alloc);
		}
    };
};

#endif