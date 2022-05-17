#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"
# include <iostream>
# include "bst_iterator.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"
namespace ft {
	template< class T, class Compare, class value_alloc = std::allocator<T>, class Node = ft::node<T>, class node_alloc = std::allocator<ft::node<T> > >
    class BST {
    public:
		typedef T value_type;
		typedef typename ft::bst_iterator<value_type, Compare> iterator;
		typedef typename ft::const_bst_iterator<value_type, Compare> const_iterator;
		typedef Compare key_compare;
		typedef size_t size_type;
		typedef typename value_type::first_type key_type;
		typedef typename value_type::second_type second_type;
		typedef Node typenode;
    private:
    	Node			*_root;
    	node_alloc		_node_alloc;
    	value_alloc		_value_alloc;
    	Compare			_comp;
    	size_type		_size;
		Node			*_end;

    	void	suppress_BST(Node *node_to_suppr) {
			if (node_to_suppr == _end)
				return ;
    		if (node_to_suppr->_left) {
    			suppress_BST(node_to_suppr->_left);
    		}
    		if (node_to_suppr->_right) {
    			suppress_BST(node_to_suppr->_right);
    		}
			if (_size != 0 && node_to_suppr->_value != NULL) {
				--_size;
    			_value_alloc.destroy(node_to_suppr->_value);
			}
			_value_alloc.deallocate(node_to_suppr->_value, 1);			
    		_node_alloc.destroy(node_to_suppr);
			_node_alloc.deallocate(node_to_suppr, 1);
    	}

    	Node *alloc_new_node(void) {
    		Node *new_node;

    		new_node = _node_alloc.allocate(1);
    		_node_alloc.construct(new_node, Node());
			new_node->_value = _value_alloc.allocate(1);
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

    		_comp = comp;
    		this->initialize();
    		this->add_range(first, last);
    	}

    	~BST() {
    		if (_root)
    			suppress_BST(_root);
			_value_alloc.deallocate(_end->_value, 1);
    		_node_alloc.destroy(_end);
			_node_alloc.deallocate(_end, 1);
    	}

		BST& operator= (const BST& x) {
			std::cout << "hello"<< std::endl;
			if (this == &x)
				return (*this);
			_comp = x._comp;
			_node_alloc = x._node_alloc;
			_value_alloc = x._value_alloc;
			_size = x._size;
			_root = x._root;
			_end = x._end;
			return (*this);
		}

    	void clear() {
    		if (_root)
    			suppress_BST(_root);
			_value_alloc.deallocate(_end->_value, 1);
			_node_alloc.destroy(_end);
			_node_alloc.deallocate(_end, 1);
			this->initialize();
    	}

    	void initialize(const key_compare comp = key_compare()) {
			_node_alloc = node_alloc();
			_value_alloc = value_alloc();
    		_root = alloc_new_node();
    		_comp = comp;
    		_size = 0;
			_end = alloc_new_node();
			_root->_right = _end;
			_end->_parent = _root;
			_end->_black = true;
    	}

		iterator begin() {
			if (_size == 0)
				return (iterator(_end));
			Node *head = _root;
			while (head->_left)
				head = head->_left;
			return (iterator(head));
		}

		iterator end() { 
			return (iterator(_end));
		}

		const_iterator begin() const {
			if (_size == 0)
				return (const_iterator(_end));
			Node *head = _root;
			while (head->_left)
				head = head->_left;
			return (const_iterator(head));
		}

		const_iterator end() const { 
			return (const_iterator(_end));
		}

    	void display_recursif(Node *node_to_disp, int level, bool debug) {
    		if (node_to_disp->_left) {
    			display_recursif(node_to_disp->_left, level + 1, debug);
    		}
    		if (node_to_disp->_right) {
    			display_recursif(node_to_disp->_right, level + 1, debug);
    		}
			if (node_to_disp == _end) {
				return ;
			}
			if (debug) {
				std::cout << "LEVEL : " << level << " ( " << node_to_disp <<" ) // " << node_to_disp->_value->first
				<< " // LEFT : " << node_to_disp->_left << " // RIGHT : " << node_to_disp->_right << " // black : " << node_to_disp->_black <<  " // PARENT : " << node_to_disp->_parent << std::endl;
			}
			else {
				std::cout << "(" << level << ")" << node_to_disp->_value->first << ";";
				if (node_to_disp == _root)
					std::cout << std::endl;
			}
    	}

    	void display_tree(bool debug) {
    		std::cout << "tree size : " << _size << std::endl;
    		if (_size != 0)
    			display_recursif(_root, 0, debug);
    	}

    	size_type	size() const {return _size;}

		void replace_node(Node *old, Node *new_n) {
		    if (old->_parent == NULL) {
		        _root = new_n;
		    }
		    else {
		        if (old == old->_parent->_left)
		            old->_parent->_left = new_n;
		        else
		            old->_parent->_right = new_n;
		    }
		    if (new_n != NULL) {
		        new_n->_parent = old->_parent;
		    }
		}

		void rotate_left(Node *to_rot) {
		    Node *right = to_rot->_right;
		    replace_node(to_rot, right);
		    to_rot->_right = right->_left;
		    if (right->_left != NULL) {
		        right->_left->_parent = to_rot;
		    }
		    right->_left = to_rot;
		    to_rot->_parent = right;
		}

		void rotate_right(Node *to_rot) {
		    Node *left = to_rot->_left;
		    replace_node(to_rot, left);
		    to_rot->_left = left->_right;
		    if (left->_right != NULL) {
		        left->_right->_parent = to_rot;
		    }
		    left->_right = to_rot;
		    to_rot->_parent = left;
		}

		bool is_node_black(Node *node) {
			if (!node)
				return (true);
			return (node->_black);
		}

		Node *grand_parent(Node *node) {
			if (node->_parent == NULL)
				return (NULL);
			return (node->_parent->_parent);			
		}

		Node *sibling(Node *node) {
			if (node->_parent == NULL)
				return (NULL);
			if (node->_parent->_left == node)
				return (node->_parent->_right);
			return (node->_parent->_left);
		}

		Node *oncle(Node *node) {
			if (!grand_parent(node))
				return (NULL);
			if (node->_parent == node->_parent->_parent->_left)
				return (node->_parent->_parent->_right);
			else
				return (node->_parent->_parent->_left);
		}

		Node *assertion(Node *n, bool left) {
			if (!n)
				return (NULL);
			if (left)
				return (n->_left);
			return (n->_right);
		}

		void insert_case_1(Node *new_node) {
			if (new_node->_parent == NULL)
				new_node->_black = true;
			else
				insert_case_2(new_node);
		}

		void insert_case_2(Node *new_node) {
			if (!new_node->_parent->_black) 
				insert_case_3(new_node);
		}

		void insert_case_3(Node *new_node) {
			if (!is_node_black(oncle(new_node))) {
				if (oncle(new_node))
					oncle(new_node)->_black = true;
				new_node->_parent->_black = true;
				if (grand_parent(new_node))
					grand_parent(new_node)->_black = false;
				insert_case_1(grand_parent(new_node));
			}
			else
				insert_case_4(new_node);
		}

		void insert_case_4(Node *new_node) {
		    if (new_node == new_node->_parent->_right && new_node->_parent == grand_parent(new_node)->_left) {
		        rotate_left(new_node->_parent);
		        new_node = new_node->_left;
		    }
		    else if (new_node == new_node->_parent->_left && new_node->_parent == grand_parent(new_node)->_right) {
		        rotate_right(new_node->_parent);
		        new_node = new_node->_right;
		    }
		    insert_case_5(new_node);
		}

		void insert_case_5(Node *new_node) {
			new_node->_parent->_black = true;
			grand_parent(new_node)->_black = false;
			if (new_node == new_node->_parent->_left && new_node->_parent == grand_parent(new_node)->_left)
				rotate_right(grand_parent(new_node));
			else if (new_node == new_node->_parent->_right && new_node->_parent == grand_parent(new_node)->_right)
				rotate_left(grand_parent(new_node));
		}


    	ft::pair<iterator,bool> add(const T& pair, bool hint = false, iterator hint_it = NULL) {
    		if (_size == 0) {
    			++_size;
				_value_alloc.construct(_root->_value, pair);
				insert_case_1(_root);
    			return (ft::pair<iterator,bool>(iterator(_root), true));
    		}

    		Node *next;
    		Node *parent;

    		if (hint && hint_it != this->end()) {
    			while (hint_it.base() != _end && _comp(hint_it->first, pair.first))
    				++hint_it;
    			if (hint_it.base() == _end)
    				--hint_it;
    			while (hint_it != this->begin() && _comp(pair.first, hint_it->first))
    				--hint_it;
    			next = hint_it.base();
    		}
    		else
    			next = _root;
    		while (next != NULL && next != _end) {
    			parent = next;
    			if (_comp(pair.first, next->_value->first))
    				next = next->_left;
    			else if (_comp(next->_value->first, pair.first))
    				next = next->_right;
    			else
    				return (ft::pair<iterator,bool>(iterator(next), false));
    		}
     		Node *new_node = alloc_new_node();
    		_value_alloc.construct(new_node->_value, pair);
    		new_node->_black = false;
			if (_comp(pair.first, parent->_value->first))
				parent->_left = new_node;
			else if (!_comp(pair.first, parent->_value->first))
				parent->_right = new_node;
			new_node->_parent = parent;
			if (next == _end) {
				new_node->_right = _end;
				_end->_parent = new_node;
			}
    		++_size;
			insert_case_1(new_node);
			return (ft::pair<iterator,bool>(iterator(new_node), true));
		}

		void swap_node(Node *n1, Node *n2) {
			Node *parent_tmp = n1->_parent;
			Node *left_tmp = n1->_left;
			Node *right_tmp = n1->_right;
			bool black_tmp = n1->_black;

			if (n1->_parent && n1->_parent->_left == n1)
				n1->_parent->_left = n2;
			else if (n1->_parent)
				n1->_parent->_right = n2;
			else
				_root = n2;
			if (n2->_parent && n2->_parent->_left == n2)
				n2->_parent->_left = n1;
			else if (n2->_parent)
				n2->_parent->_right = n1;
			else
				_root = n1;

			n1->_parent = (n2->_parent == n1) ? n2 : n2->_parent;
			n1->_left = n2->_left;
			n1->_right = n2->_right;
			if (n1->_right)
				n1->_right->_parent = n1;
			if (n1->_left)
				n1->_left->_parent = n1;
			n1->_black = n2->_black;
			n2->_parent = parent_tmp;
			n2->_left = (left_tmp == n2) ? n1 : left_tmp;
			n2->_right = (right_tmp == n2) ? n1 : right_tmp;
			if (n2->_right)
				n2->_right->_parent = n2;
			if (n2->_left)
				n2->_left->_parent = n2;
			n2->_black = black_tmp;

		}

		void delete_case_1(Node *n) {
			if (n->_parent)
				delete_case_2(n);
		}

		void delete_case_2(Node *n) {
			if (!is_node_black(sibling(n))) {
				n->_parent->_black = false;
				sibling(n)->_black = true;
				if (n->_parent->_left == n)
					rotate_left(n->_parent);
				else
					rotate_right(n->_parent);
			}
			delete_case_3(n);
		}

		void delete_case_3(Node *n) {
			if (is_node_black(n->_parent) && is_node_black(sibling(n))
				&& is_node_black(assertion(sibling(n), true)) && is_node_black(assertion(sibling(n), false))) {
				if (sibling(n))
					sibling(n)->_black = false;
				delete_case_1(n->_parent);
			}
			else
				delete_case_4(n);
		}

		void delete_case_4(Node *n) {
			if (!is_node_black(n->_parent) && is_node_black(sibling(n))
				&& is_node_black(assertion(sibling(n), true)) && is_node_black(assertion(sibling(n), false))) {
				if (sibling(n))
					sibling(n)->_black = false;
				n->_parent->_black = true;
			}
			else
				delete_case_5(n);
		}

		void delete_case_5(Node *n) {
			if (sibling(n) && n->_parent->_left == n && is_node_black(sibling(n)) && sibling(n)
				&& !is_node_black(sibling(n)->_left) && is_node_black(sibling(n)->_right)) {
				sibling(n)->_black = false;
				sibling(n)->_left->_black = true;
				rotate_right(sibling(n));
			}
			else if (sibling(n) && n->_parent->_right == n && is_node_black(sibling(n)) && sibling(n)
				&& is_node_black(sibling(n)->_left) && !is_node_black(sibling(n)->_right)) {
				sibling(n)->_black = false;
				sibling(n)->_right->_black = true;
				rotate_left(sibling(n));
			}
			else
				delete_case_6(n);
		}

		void delete_case_6(Node *n) {
			if (sibling (n))
				sibling(n)->_black = is_node_black(n->_parent);
			n->_parent->_black = true;
			if (sibling(n) && n->_parent->_left == n && !is_node_black(sibling(n)->_right)) {
				sibling(n)->_right->_black = true;
				rotate_left(n->_parent);
			}
			else if (sibling(n) && n->_parent->_right == n && !is_node_black(sibling(n)->_left)) {
				sibling(n)->_left->_black = true;
				rotate_right(n->_parent);
			}
		}

		template<class InputIterator>
		void	add_range(InputIterator first, InputIterator last) {
    		while (first != last) {
    			this->add(*(first++));
    		}
		}

		iterator lower_bound (const key_type& k) {
			Node *head = _root;
			iterator candidate = this->end();

			while (_size && head && head != _end) {
				if (!_comp(head->_value->first, k))
					candidate = head;
				if (_comp(k, head->_value->first))
					head = head->_left;
				else if (_comp(head->_value->first, k))
					head = head->_right;
				else
					return (candidate);
			}
			return (candidate);
		}

		iterator upper_bound (const key_type& k) {
			Node *head = _root;
			iterator candidate = this->end();

			while (_size && head && head != _end) {
				if (_comp(k, head->_value->first))
					candidate = head;
				if (_comp(k, head->_value->first))
					head = head->_left;
				else
					head = head->_right;
			}
			return (candidate);
		}

		iterator find (const key_type& k) {
			Node *head = _root;

			while (_size && head && head != _end) {
				if (_comp(head->_value->first, k))
					head = head->_right;
				else if (_comp(k, head->_value->first))
					head = head->_left;
				else
					return (iterator(head));
			}
			return (this->end());
		}

		const_iterator find (const key_type& k) const {
			Node *head = _root;

			while (_size && head && head != _end) {
				if (_comp(head->_value->first, k))
					head = head->_right;
				else if (_comp(k, head->_value->first))
					head = head->_left;
				else
					return (iterator(head));
			}
			return (this->end());
		}

		void destroy_node(Node *suppr_node) {
			_value_alloc.destroy(suppr_node->_value);
			_value_alloc.deallocate(suppr_node->_value, 1);
			_node_alloc.destroy(suppr_node);
			_node_alloc.deallocate(suppr_node, 1);
		}

		void erase(iterator position) {
			Node *to_suppr = position.base();
			--_size;
			if (_size == 0) {
				this->clear();
				return ;
			}
			if (to_suppr->_left && to_suppr->_right) {
				Node *replacement = rightest_from(to_suppr->_left);
				swap_node(to_suppr, replacement);
			}
			Node *children = to_suppr->_right ? to_suppr->_right : to_suppr->_left;
			if (is_node_black(to_suppr)) {
				to_suppr->_black = is_node_black(children);
				delete_case_1(to_suppr);
			}
			replace_node(to_suppr, children);
			if (!to_suppr->_parent && children)
				children->_black = true;
			destroy_node(to_suppr);
		}

		size_type erase (const key_type& k) {
			iterator locate = this->find(k);
			if (locate == this->end()) {
				return (0);
			}
			this->erase(locate);
			return (1);
		}

		void erase (iterator first, iterator last) {
			if (first == last)
				return ;
			iterator head = last;
			key_type stop_val = first->first;
			while (1) {
				if ((--head)->first == stop_val) 
					break ;
				this->erase(head);
				head = last;
			}
			this->erase(head);
		}


		void swap (BST& x) {
	    	Node			*tmp_root = _root;
	    	node_alloc		tmp_node_alloc = _node_alloc;
	    	value_alloc		tmp_value_alloc = _value_alloc;
	    	Compare			tmp_comp = _comp;
	    	size_type		tmp_size = _size;
			Node			*tmp_end = _end;

			_root = x._root;
			_node_alloc = x._node_alloc;
			_value_alloc = x._value_alloc;
			_comp = x._comp;
			_size = x._size;
			_end = x._end;

			x._root = tmp_root;
			x._node_alloc = tmp_node_alloc;
			x._value_alloc = tmp_value_alloc;
			x._comp = tmp_comp;
			x._size = tmp_size;
			x._end = tmp_end;
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
			friend class map<key_type, mapped_type, key_compare, Alloc>;
		protected:
			Compare _comp;

			value_compare(Compare comp = key_compare()) : _comp(comp) {};

		public:
			typedef bool result_type;
			typedef value_type first_argument_type;
			typedef value_type second_argument_type;
			bool operator() (const value_type& x, const value_type& y) const {
				return (_comp(x.first, y.first));
			}
		};
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::BST<value_type, key_compare>::iterator iterator;
		typedef typename ft::BST<value_type, key_compare>::const_iterator const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;	
		typedef typename ft::iterator_traits<iterator>::difference_type difference_type;
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
			_bst.clear();
			_bst.add_range(x.begin(), x.end());
			return (*this);
		}

		bool empty() const { return (!_bst.size()); }
		size_type size() const { return (_bst.size()); }
		size_type max_size() const { std::allocator<ft::node<T> > alloc_node; return (alloc_node.max_size()); }

		pair<iterator,bool> insert (const value_type& val) {
			return (_bst.add(val));
		}

		iterator insert (iterator position, const value_type& val) {
			return (_bst.add(val, true, position).first);	
		}

		template <class InputIterator>
 		void insert (InputIterator first, InputIterator last) {
 			_bst.add_range(first, last);
  		}

		void erase (iterator position) {
			return (_bst.erase(position));
		}

		size_type erase (const key_type& k) {
			return (_bst.erase(k));
		}

		void erase (iterator first, iterator last) {
			return (_bst.erase(first, last));
		}

		void clear() {
			_bst.clear();
		}

		iterator begin() {return _bst.begin();}
		const_iterator begin() const { return const_iterator(_bst.begin());}

		iterator end() {return _bst.end();}
		const_iterator end() const {return const_iterator(_bst.end());}

		reverse_iterator rbegin() {return reverse_iterator(_bst.end());}

		reverse_iterator rend() {return reverse_iterator(_bst.begin());}

		const_reverse_iterator rbegin() const {return const_reverse_iterator(_bst.end());}

		const_reverse_iterator rend() const {return const_reverse_iterator(_bst.begin());}

		mapped_type& operator[] (const key_type& k) {
			iterator it = _bst.find(k);
			if (it != this->end())
				return (it->second);
			ft::pair<key_type,mapped_type> pair;
			pair.first = k;
			return (_bst.add(pair).first->second);
		}


		void display_tree(bool debug = false) {
			_bst.display_tree(debug);
		}

		void swap (map& x) {
			key_compare		tmp_comp = _comp;
			allocator_type	tmp_alloc = _alloc;

			_bst.swap(x._bst);
			_alloc = x._alloc;
			_comp = x._comp;

			x._alloc = tmp_alloc;
			x._comp = tmp_comp;
		}

		iterator find (const key_type& k) { return (_bst.find(k)); }

		const_iterator find (const key_type& k) const { return (const_iterator(_bst.find(k))); }

		size_type count (const key_type& k) const { return ((_bst.find(k) != this->end())); }

		iterator lower_bound (const key_type& k) { return (_bst.lower_bound(k)); }

		iterator upper_bound (const key_type& k) { return (_bst.upper_bound(k)); }

		const_iterator lower_bound (const key_type& k) const { return (const_iterator(_bst.lower_bound(k))); }

		const_iterator upper_bound (const key_type& k) const { return (const_iterator(_bst.upper_bound(k))); }

		key_compare key_comp() const { return (_comp) ; }

		value_compare value_comp() const { return (value_compare()); }

		ft::pair<iterator,iterator> equal_range (const key_type& k) {
			iterator it = _bst.find(k);
			iterator end = _bst.end();
			if (it == end) {
				it = _bst.upper_bound(k);
				return (ft::pair<iterator,iterator>(it, it));
			}
			iterator itplus = it;
			return (ft::pair<iterator,iterator>(it, ++itplus));
		}

		ft::pair< const_iterator, const_iterator> equal_range (const key_type& k) const {
			const_iterator it = _bst.find(k);
			const_iterator end = _bst.end();
			if (it == end) {
				it = _bst.upper_bound(k);
				return (ft::pair<const_iterator,const_iterator>(it, it));
			}
			const_iterator itplus = it;
			return (ft::pair<const_iterator,const_iterator>(it, ++itplus));
		}

		allocator_type get_allocator() const { return (_alloc); }

	private:
		key_compare							_comp;
		allocator_type						_alloc;
		ft::BST<value_type, key_compare>	_bst;
	};


}

#endif
