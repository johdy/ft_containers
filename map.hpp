#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"
# include <iostream>
# include "iterators/bst_iterator.hpp"
# include "utils.hpp"
namespace ft {
	template< class T, class Compare, class value_alloc = std::allocator<T>, class Node = ft::node<T>, class node_alloc = std::allocator<ft::node<T> > >
    class BST {
    public:
		typedef T value_type;
		typedef typename ft::bst_iterator<Node, value_type> iterator;
		typedef Compare key_compare;
		typedef size_t size_type;
		typedef typename value_type::first_type key_type;
		typedef typename value_type::second_type second_type;
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
    		--_size;
		//	if (node_to_suppr->_value != NULL)
    	//		_value_alloc.destroy(node_to_suppr->_value);
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

		void	add_range_except(iterator first, iterator last_included, iterator avoid) {
    		iterator middle = first;
    		iterator to_suppr = first++;
    		/*size_t size = 0;

   			while (middle != last_included) {
    			++size;
    			++middle;
    		}
    		if (size == 0)
    			return ;
    		size = size / 2 + 1;
    		while (--size)
    			--middle;
    		if (middle != avoid)
    			this->re_add(middle.base());
    		iterator middle2 = middle;
    		iterator it = middle;
    		iterator it2 = ++middle2;
  			std::cout << size << std::endl;
	  		while (it != first && it2 != last_included) {
    			if (it != avoid)
    				this->re_add(it.base());
    			if (it2 != avoid)
    				this->re_add(it2.base());
    			it = middle--;
    			it2 = middle2++;
    			it.base()->_left = NULL;
    			it.base()->_right = NULL;
    			it2.base()->_left = NULL;
    			it2.base()->_right = NULL;
    			std::cout << it->first << "/" << first->first << it2->first << last_included->first << std::endl;
    		}
	   		it = middle;
	   		iterator 
    		while (it++ != last_included) {
    			if (it != avoid)
    				this->re_add(*it);
    		}
    		*/
    		std::cout << last_included->first << std::endl;
    		while (to_suppr != last_included && to_suppr.base() != _end) {
    			std::cout << to_suppr->first << std::endl;
    			to_suppr.base()->_left = NULL;
    			to_suppr.base()->_right = NULL;
    			if (to_suppr != avoid)
    				re_add(to_suppr.base());
    			std::cout << to_suppr->first << std::endl;
    			to_suppr = first++;
	 		}
			//std::cout << to_suppr->first << std::endl;
			to_suppr.base()->_left = NULL;
			to_suppr.base()->_right = NULL;
			if (to_suppr != avoid)
				re_add(to_suppr.base());
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
			_value_alloc.deallocate(_end->_value, 1);
    		_node_alloc.destroy(_end);
			_node_alloc.deallocate(_end, 1);
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
    	}

		iterator begin() const {
			if (_size == 0)
				return (iterator(_end));
			Node *head = _root;
			while (head->_left)
				head = head->_left;
			return (iterator(head));
		}

		iterator end() const { 
			return (iterator(_end));
		}

    	void display_recursif(Node *node_to_disp, int level, bool debug) {
    		if (node_to_disp->_left) {
    			display_recursif(node_to_disp->_left, level + 1, debug);
    		}
    		if (node_to_disp->_right) {
    			display_recursif(node_to_disp->_right, level + 1, debug);
    		}
			if (node_to_disp == _end)
				return ;
			if (debug) {
				std::cout << "LEVEL : " << level << " ( " << node_to_disp <<" ) // " << node_to_disp->_value->first << " : " << node_to_disp->_value->second
				<< " // LEFT : " << node_to_disp->_left << " // RIGHT : " << node_to_disp->_right << std::endl;
			}
			else {
				std::cout << "(" << level << ")" << node_to_disp->_value->first << ":" << node_to_disp->_value->second << ";";
				if (node_to_disp == _root)
					std::cout << std::endl;
			}
    	}

    	void display_tree(bool debug) {
    		std::cout << "tree size : " << _size << std::endl;
    		display_recursif(_root, 0, debug);
    	}

    	size_type	size() const {return _size;}

    	ft::pair<iterator,bool> re_add(Node *node, bool hint = false, iterator hint_it = NULL) {
    		Node *next;
    		Node *parent;

    		if (hint)
    			 next = hint_it.base();
    		else
    			next = _root;
    		while (next != NULL && next != _end) {
    			parent = next;
    			if (_comp(node->_value->first, next->_value->first))
    				next = next->_left;
    			else if (_comp(next->_value->first, node->_value->first))
    				next = next->_right;
    			else
    				return (ft::pair<iterator,bool>(iterator(next), false));
    		}
			if (_comp(node->_value->first, parent->_value->first))
				parent->_left = node;
			else if (!_comp(node->_value->first, parent->_value->first))
				parent->_right = node;
			node->_parent = parent;
			if (next == _end) {
				node->_right = _end;
				_end->_parent = node;
			}
			return (ft::pair<iterator,bool>(iterator(node), true));
		}

    	ft::pair<iterator,bool> add(const T& pair, bool hint = false, iterator hint_it = NULL) {
    		++_size;
    		if (_root->_parent == NULL) {
				_value_alloc.construct(_root->_value, pair);
    			//_root->_value = pair;
    			_root->_parent = _root;
    			return (ft::pair<iterator,bool>(iterator(_root), true));
    		}

    		Node *next;
    		Node *parent;

    		if (hint)
    			 next = hint_it.base();
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
			if (_comp(pair.first, parent->_value->first))
				parent->_left = new_node;
			else if (!_comp(pair.first, parent->_value->first))
				parent->_right = new_node;
			new_node->_parent = parent;
			if (next == _end) {
				new_node->_right = _end;
				_end->_parent = new_node;
			}
			return (ft::pair<iterator,bool>(iterator(new_node), true));
		}

		template<class InputIterator>
		void	add_range(InputIterator first, InputIterator last, InputIterator avoid = NULL) {
    		InputIterator middle = first;
    		size_t size = 0;

    		while (middle != last) {
    			++size;
    			++middle;
    		}
    		size = size / 2 + 1;
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

		iterator lower_bound (const key_type& k) {
			Node *head = _root;
			iterator candidate = this->end();

			while (head) {
				if (!_comp(head->_value->first, k))
					candidate = head;
				if (_comp(k, head->_value->first))
					head = head->_left;
				else if (_comp(head->_value->first, k))
					head = head->_right;
				else
					return (candidate);
			}
			return (this->end());
		}

		iterator upper_bound (const key_type& k) {
			Node *head = _root;
			iterator candidate = this->end();

			while (head) {
				if (_comp(k, head->_value->first))
					candidate = head;
				if (_comp(k, head->_value->first))
					head = head->_left;
				else
					head = head->_right;
			}
			return (candidate);
		}


		iterator find (const key_type& k) const {
			Node *head = _root;

			while (head && head != _end) {
				if (_comp(head->_value->first, k))
					head = head->_right;
				else if (_comp(k, head->_value->first))
					head = head->_left;
				else
					return (iterator(head));
			}
			return (this->end());
		}

		void root_erasing(Node *val) {
			_root = val;
			_root->_parent = _root;
			_root->_right = _end;
			_end->_parent = _root;
			return;
		}

		void erase(iterator position) {
			Node *suppr_node = position.base();
			Node *determine_range = suppr_node;

			--_size;
			display_tree(true);
			if (suppr_node == _root) {
				iterator beg = begin();
				iterator en = --end();
				if (_root->_left != NULL)
					root_erasing(_root->_left);
				else if (_root->_right != NULL && _root->_right != _end)
					root_erasing(_root->_right);
				else {
					this->clear();
					return ;
				}
				std::cout << "new_root:" << _root->_value->first << std::endl;
				this->add_range_except(beg, en, position);
				//this->suppress_BST(suppr_node);
				std::cout << "ERASE ROOT" << std::endl;
				display_tree(true);
				return;
			}
			if (suppr_node->_parent->_left == suppr_node)
				suppr_node->_parent->_left = NULL;
			else
				suppr_node->_parent->_right = NULL;

			while (determine_range->_left)
				determine_range = determine_range->_left;
			iterator first(determine_range);
			determine_range = suppr_node;
			while (determine_range->_right && determine_range->_right != _end)
				determine_range = determine_range->_right;
			if (determine_range->_right == _end) {
				suppr_node->_parent->_right = _end;
				_end->_parent = suppr_node->_parent;
			}
			iterator last(determine_range);
			this->add_range_except(first, last, position);
			_value_alloc.destroy(suppr_node->_value);
			_value_alloc.deallocate(suppr_node->_value, 1);
			_node_alloc.destroy(suppr_node);
			_node_alloc.deallocate(suppr_node, 1);
			//this->suppress_BST(suppr_node);
		}

		void destroy_node(Node *suppr_node) {
			_value_alloc.destroy(suppr_node->_value);
			_value_alloc.deallocate(suppr_node->_value, 1);
			_node_alloc.destroy(suppr_node);
			_node_alloc.deallocate(suppr_node, 1);			
		}

		iterator sew_remaining_nodes(iterator position) {
			Node *leftest_from_right;

			leftest_from_right = position.base()->_right;
			while (leftest_from_right && leftest_from_right->_left)
				leftest_from_right = leftest_from_right->_left;
			if (!leftest_from_right)
				position.base()->_right = position.base()->_left;
			else
				leftest_from_right->_left = position.base()->_left;

			Node *last_node = position.base()->_right;
			while (last_node->_right && last_node->_right != _end)
				last_node = last_node->_right;
			last_node->_right = _end;

			while (leftest_from_right->_left)
				leftest_from_right = leftest_from_right->_left;
			return (iterator(leftest_from_right));
		}

		void erase(iterator position) {
			Node *suppr_node = position.base();
			Node *determine_range = suppr_node;

			--_size;
			display_tree(true);
			if (suppr_node == _root) {
				iterator beg = begin();
				iterator en = --end();
				if (_root->_left != NULL)
					root_erasing(_root->_left);
				else if (_root->_right != NULL && _root->_right != _end)
					root_erasing(_root->_right);
				else {
					this->clear();
					return ;
				}
				std::cout << "new_root:" << _root->_value->first << std::endl;
				this->add_range_except(beg, en, position);
				//this->suppress_BST(suppr_node);
				std::cout << "ERASE ROOT" << std::endl;
				display_tree(true);
				return;
			}
			//COUD
			iterator first_to_readd = sew_remaining_nodes(position);

			//COUPE
			if (suppr_node->_parent->_left == suppr_node)
				suppr_node->_parent->_left = NULL;
			else
				suppr_node->_parent->_right = NULL;
			destroy_node(suppr_node);

			//REINJECTE
			readd_range(first_to_readd);

			//this->suppress_BST(suppr_node);
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
			iterator head = last;
			key_type stop_val = first->first;
			std::cout << "heo" << std::endl;
			while (1) {
				if ((--head)->first == stop_val) 
					break ;
				std::cout << head->first << std::endl;
				this->erase(head);
				head = last;
			}
			this->erase(head);
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
			_bst.add_range(x.begin(), x.end());
			return (*this);
		}

		bool empty() const { return (!_bst.size()); }
		size_type size() const { return (_bst.size()); }
		size_type max_size() const { return (_alloc.max_size()); }

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

		iterator begin() const {return _bst.begin();}
		//const_iterator begin() {return _bst.begin();}

		iterator end() const {return _bst.end();}
		//const_iterator end() {return _bst.end();}

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
			key_compare							tmp_comp = _comp;
			allocator_type						tmp_alloc = _alloc;
			ft::BST<value_type, key_compare>	tmp_bst = _bst;

			_bst = x._bst;
			_alloc = x._alloc;
			_comp = x._comp;

			x._bst = tmp_bst;
			x._alloc = tmp_alloc;
			x._comp = tmp_comp;
		}

		iterator find (const key_type& k) { return (_bst.find(k)); }

		size_type count (const key_type& k) const { return ((_bst.find(k) != this->end())); }

		iterator lower_bound (const key_type& k) { return (_bst.lower_bound(k)); }

		iterator upper_bound (const key_type& k) { return (_bst.upper_bound(k)); }

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

		ft::pair< const iterator, const iterator> equal_range (const key_type& k) const {
			iterator it = _bst.find(k);
			iterator end = _bst.end();
			if (it == end) {
				it = _bst.upper_bound(k);
				return (ft::pair<iterator,iterator>(it, it));
			}
			iterator itplus = it;
			return (ft::pair<iterator,iterator>(it, ++itplus));
		}

		allocator_type get_allocator() const { return (_alloc); }

	private:
		key_compare							_comp;
		allocator_type						_alloc;
		ft::BST<value_type, key_compare>	_bst;
	};


}

#endif
