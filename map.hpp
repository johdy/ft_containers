#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"
# include <iostream>
# include "iterators/bst_iterator.hpp"
namespace ft {
	template< class T, class Compare = std::less<T>, class Node = ft::node<T>, class node_alloc = std::allocator<ft::node<T> > >
    class BST {
    private:
    	Node			*_root;
    	node_alloc		_node_alloc;

    	void	suppress_BST(Node *node_to_suppr) {
    		if (node_to_suppr->_left) {
    			suppress_BST(node_to_suppr->_left);
    		}
    		if (node_to_suppr->_right) {
    			suppress_BST(node_to_suppr->_right);
    		}
			_node_alloc.deallocate(node_to_suppr, 1);
    	}

    	Node *alloc_new_node(void) {
    		Node *new_node;

    		new_node = _node_alloc.allocate(1);
    		_node_alloc.construct(new_node, Node());
    		new_node->_parent = NULL;
    		new_node->_left = NULL;
    		new_node->_right = NULL;
    		return (new_node);
    	}

    public:
		typedef typename ft::bst_iterator<Node> iterator;

    	BST() : _node_alloc(node_alloc()) {
    		_root = alloc_new_node();
    	}

    	~BST() {
    		suppress_BST(_root);
    	}

		iterator begin() { return (iterator(_root)); }

    	void display_recursif(Node *node_to_disp, int level) {
    		if (node_to_disp->_left) {
    			display_recursif(node_to_disp->_left, level + 1);
    		}
    		if (node_to_disp->_right) {
    			display_recursif(node_to_disp->_right, level + 1);
    		}
			std::cout << "LEVEL : " << level << " ( " << node_to_disp <<" ) // " << node_to_disp->_value.first << " : " << node_to_disp->_value.second
			<< " // LEFT : " << node_to_disp->_left << " // RIGHT : " << node_to_disp->_right << std::endl; 		
    	}

    	void display_tree() {
    		display_recursif(_root, 0);
    	}

    	void add(T& pair) {
    		if (_root->_parent == NULL) {
    			_root->_value.first = pair.first;
    			_root->_parent = _root;
    			return ;
    		}

    		Node *next = _root->_parent;
    		Node *parent = NULL;

    		while (next != NULL) {
    			parent = next;
    			if (pair.first < next->_value.first)
    				next = next->_left;
    			else if (pair.first > next->_value.first)
    				next = next->_right;
    		}
     		Node *new_node = alloc_new_node();
    		new_node->_value = pair;

			if (pair.first < parent->_value.first)
				parent->_left = new_node;
			else if (pair.first > parent->_value.first)
				parent->_right = new_node;
			new_node->_parent = parent;
		}
	};

	template< class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
    class map {
    public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<key_type,mapped_type> value_type;
		/*typedef Compare key_compare;
		typedef value_compare	Nested function class to compare elements	see value_comp
		typedef Alloc allocator_type;
		typedef allocator_type::reference reference;
		typedef allocator_type::const_reference const_reference;
		typedef allocator_type::pointer pointer;
		typedef allocator_type::const_pointer const_pointer;
		//typedef iterator	a bidirectional iterator to value_type	convertible to const_iterator
		//typedef const_iterator	a bidirectional iterator to const value_type	
		//typedef reverse_iterator<iterator> reverse_iterator;	
		//typedef reverse_iterator<const_iterator> const_reverse_iterator;	
		typedef iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;*/
		typedef typename ft::BST<value_type>::iterator iterator;

		map() : bst() {};

		void add(value_type pair) {
			bst.add(pair);
		}

		iterator begin() {return bst.begin();}

		void display_tree() {
			bst.display_tree();
		}

	private:
		ft::BST<value_type> bst;
	};


}

#endif
