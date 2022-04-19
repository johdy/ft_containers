#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"
# include <iostream>
# include "iterators/bst_iterator.hpp"
# include "utils.hpp"
namespace ft {
	template< class T, class Compare, class Node = ft::node<T>, class node_alloc = std::allocator<ft::node<T> > >
    class BST {
    public:
		typedef T value_type;
		typedef typename ft::bst_iterator<Node, value_type> iterator;
		typedef Compare key_compare;
		typedef size_t size_type;
    private:
    	Node			*_root;
    	node_alloc		_node_alloc;
    	Compare			_comp;
    	size_type		_size;

    	void	suppress_BST(Node *node_to_suppr) {
    		if (node_to_suppr->_left) {
    			suppress_BST(node_to_suppr->_left);
    		}
    		if (node_to_suppr->_right) {
    			suppress_BST(node_to_suppr->_right);
    		}
    		_node_alloc.destroy(node_to_suppr);
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

    	BST() {
    		this->initialize();
    	}

    	template <class InputIterator>
    	BST(InputIterator first, InputIterator last,
    		const key_compare comp = key_compare()) {

    		this->initialize();
    		this->add_range(first, last);
    	}

    	~BST() {
    		if (_root)
    			suppress_BST(_root);
    	}

    	void clear() {
    		_size = 0;
    		if (_root)
    			suppress_BST(_root);
    	}

    	void initialize(const key_compare comp = key_compare()) {
			_node_alloc = node_alloc();
    		_root = alloc_new_node();
    		_comp = comp;
    		_size = 0; 		
    	}

		iterator begin() const { 
			Node *head = _root;
			while (head->_left)
				head = head->_left;
			return (iterator(head));
		}

		iterator end() const { 
			Node *head = _root;
			while (head->_right)
				head = head->_right;
			return (++iterator(head));
		}

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
    		std::cout << "tree size : " << _size << std::endl;
    		display_recursif(_root, 0);
    	}

    	size_type	size() {return _size;}

    	void add(T& pair) {
    		++_size;
    		if (_root->_parent == NULL) {
    			_root->_value = pair;
    			_root->_parent = _root;
    			return ;
    		}

    		Node *next = _root->_parent;
    		Node *parent = NULL;

    		while (next != NULL) {
    			parent = next;
    			if (_comp(pair.first, next->_value.first))
    				next = next->_left;
    			else if (!_comp(pair.first, next->_value.first))
    				next = next->_right;
    		}
     		Node *new_node = alloc_new_node();
    		new_node->_value = pair;
			if (_comp(pair.first, parent->_value.first))
				parent->_left = new_node;
			else if (!_comp(pair.first, parent->_value.first))
				parent->_right = new_node;
			new_node->_parent = parent;
		}

		template<class InputIterator>
		void	add_range(InputIterator first, InputIterator last) {
    		InputIterator middle = first;
    		size_t size = 0;

    		while (middle != last) {
    			++size;
    			++middle;
    		}
    		size = size / 2;
    		while (size--)
    			--middle;
    		this->add(*middle);
    		InputIterator it = middle;
    		while (it-- != first)
    			this->add(*it);
    		it = middle;
    		while (++it != last)
    			this->add(*it);
		}
	};

	template< class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
    class map {
    public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef ft::pair<key_type,mapped_type> value_type;
		typedef Compare key_compare;
		class value_compare {
			//friend class map<key_type, mapped_type, key_compare, Alloc>;
		protected:
			Compare _comp;

			value_compare(Compare comp) : _comp(comp) {};

		public:
			bool operator() (const value_type& x, const value_type& y) const {
				return (_comp(x.first, y.first));
			}
		};
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::BST<value_type, value_compare>::iterator iterator;
		//typedef const_iterator	a bidirectional iterator to const value_type	
		//typedef reverse_iterator<iterator> reverse_iterator;	
		//typedef reverse_iterator<const_iterator> const_reverse_iterator;	
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef size_t size_type;


		explicit map(const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()): _bst() {
			_alloc = alloc;
			_comp = comp;
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
			const allocator_type& alloc = allocator_type()) : _bst(first, last) {
			_alloc = alloc;
			_comp = comp;
		}

		map (const map& x) {
			*this = x;
		}

		~map() {
		}

		map& operator= (const map& x) {
			if (this == &x)
				return (*this);
			_comp = x._comp;
			_alloc = x._alloc;
			_bst.clear();
			_bst.initialize();
			_bst.add_range(x.begin(), x.end());
			return (*this);
		}

		bool empty() const { return (!_bst.size()); }
		size_type size() const { return (_bst.size()); }
		size_type max_size() const { return (_alloc.max_size()); }
		void insert(value_type pair) {
			_bst.add(pair);
		}

		iterator begin() const {return _bst.begin();}
		//const_iterator begin() {return _bst.begin();}

		iterator end() const {return _bst.end();}
		//const_iterator end() {return _bst.end();}

		void display_tree() {
			_bst.display_tree();
		}

	private:
		key_compare							_comp;
		allocator_type						_alloc;
		ft::BST<value_type, key_compare>	_bst;
	};


}

#endif
