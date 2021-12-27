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
            class value_compare : public std::binary_fonction<value_type, value_type, bool>
            {
                class RBTree;
                private:
                    key_compare comp;
                public:
                    value_compare(const key_compare &x): comp(x){
                    }
                    bool operator()(const value_type&x, onst value_type &y) const{
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
                if (this == &origin)
                    return (*this);
                this->clear();
                this->_alloc = origin._alloc;
                this->_node_alloc = origin._node_alloc;
                this->_comp = origin._comp;
                this->_root = _tnull;
                this->_root = this->copy_tree(nullptr, this->_root, origin._root);
            }

            node_ptr copy_tree(node_ptr parent, node_ptr node, const node_ptr ref){
                if (ref && !ref->check)
                {
                    node = copy_node(parent, nodem ref);
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

            ~RBTree(){
                this->clear();
                this->_node_alloc.deallocate(this->_tnull, 1);
            }

            void clear(){
                this->destroy_tree(this->_root);
                this->root = his->_tnull;
            }

            void destroy_tree(node_ptr node){
                if (node && !(node->check))
                    destroy_tree(node->left_child);
                if (node && !(node->right_child))
                    destroy_tree(node->right_child);
                this->_alloc.destroy(&node->data);
                this->_node_alloc.deallocate(node, 1);
            }

            node_ptr begin_node() const{
                if (this->_root && !(this->root == this->_tnull))
                    return (this->minimum(this->root));
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
			    while (node->left != _tnull)
				    node = node->left;
			    return node;
		    }

            node_ptr maximum(node_ptr node) const{
			    while (node->right != _tnull)
				    node = node->right;
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
                if (x->left != _tnull)
				    return maximum(x->left_child);
                node_ptr y = x->parent;
			    while (y != _tnull && x == y->left_child)
			    {
				    x = y;
				    y = y->parent;
			    }
                return (y);
            }
            

    };
}

#endif