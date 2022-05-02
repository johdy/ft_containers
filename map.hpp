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
    	Compare			_comp;
    	size_type		_size;

    	void	suppress_BST(Node *node_to_suppr) {
    		if (node_to_suppr->_left) {
    			suppress_BST(node_to_suppr->_left);
    		}
    		if (node_to_suppr->_right) {
    			suppress_BST(node_to_suppr->_right);
    		}
    		--_size;
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

		void	add_range_except(iterator first, iterator last, iterator avoid) {
    		iterator middle = first;
    		size_t size = 0;

    		while (middle != last) {
    			++size;
    			++middle;
    		}
    		if (size == 0)
    			return ;
    		size = size / 2 + 1;
    		while (size--)
    			--middle;
    		if (middle != avoid)
    			this->add(*middle);
    		iterator it = middle;
	  		while (it-- != first) {
    			if (it != avoid)
    				this->add(*it);
    		}
	   		it = middle;
    		while (++it != last) {
    			if (it != avoid)
    				this->add(*it);
    		}
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

    	ft::pair<iterator,bool> add(const T& pair, bool hint = false, iterator hint_it = NULL) {
    		++_size;
    		if (_root->_parent == NULL) {
    			_root->_value = pair;
    			_root->_parent = _root;
    			return (ft::pair<iterator,bool>(iterator(_root), true));
    		}

    		Node *next;
    		Node *parent;

    		if (hint)
    			 next = hint_it.base();
    		else
    			next = _root;
    		while (next != NULL) {
    			parent = next;
    			if (_comp(pair.first, next->_value.first))
    				next = next->_left;
    			else if (_comp(next->_value.first, pair.first))
    				next = next->_right;
    			else
    				return (ft::pair<iterator,bool>(iterator(next), false));
    		}
     		Node *new_node = alloc_new_node();
    		new_node->_value = pair;
			if (_comp(pair.first, parent->_value.first))
				parent->_left = new_node;
			else if (!_comp(pair.first, parent->_value.first))
				parent->_right = new_node;
			new_node->_parent = parent;
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
				if (!_comp(head->_value.first, k))
					candidate = head;
				if (_comp(k, head->_value.first))
					head = head->_left;
				else if (_comp(head->_value.first, k))
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
				if (_comp(k, head->_value.first))
					candidate = head;
				if (_comp(k, head->_value.first))
					head = head->_left;
				else
					head = head->_right;
			}
			return (candidate);
		}


		iterator find (const key_type& k) const {
			Node *head = _root;

			while (head) {
				if (_comp(head->_value.first, k))
					head = head->_right;
				else if (_comp(k, head->_value.first))
					head = head->_left;
				else
					return (iterator(head));
			}
			return (this->end());
		}

		void root_erasing(Node *val) {
			Node *new_root = alloc_new_node();

			new_root->_value = val->_value;
			_root = new_root;
			_root->_parent = _root;
			return;
		}

		void erase(iterator position) {
			Node *suppr_node = position.base();
			Node *determine_range = suppr_node;

			if (suppr_node == _root) {
				std::cout << _size << std::endl;
				if (_size == 1) {
					clear();
					std::cout << "ohohoh" << std::endl;
					return ;
				}
				iterator beg = begin();
				iterator en = end();
				if (_root->_left != NULL)
					root_erasing(_root->_left);
				else if (_root->_right != NULL)
					root_erasing(_root->_right);
				this->add_range_except(beg, en, position);
				this->suppress_BST(suppr_node);
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
			while (determine_range->_right)
				determine_range = determine_range->_right;
			iterator last(determine_range);
			std::cout << "helo" << std::endl;
			this->add_range_except(first, last, position);
			this->suppress_BST(suppr_node);
		}

		size_type erase (const key_type& k) {
			iterator locate = this->find(k);

			if (locate == this->end()) {
				std::cout << end()->first << std::endl;
				return (0);
			}
			std::cout << "ben" << std::endl;
			this->erase(locate);
			return (1);
		}

		void erase (iterator first, iterator last) {
			iterator mem_beg = this->begin();
			iterator mem_end = --(this->end());

			size_t size_beg = 0;
			iterator beg = this->begin();
			Node *old_root = _root;

			while (beg++ != first)
				++size_beg;
			--beg;
			size_t size_end = 0;
			iterator end = this->end();
			while (end-- != last)
				++size_end;

			std::cout << "sizes " << size_beg << " // " << size_end << std::endl;
			size_t i = 0;
			iterator middle_to_end;
			if (size_beg > size_end) {
				while (size_beg - i++ > (size_beg + size_end) / 2)
					--beg;
				middle_to_end = beg;
			}
			else {
				while (size_end - i++ > (size_beg + size_end) / 2)
					++end;
				middle_to_end = end;
			}
			std::cout << (*middle_to_end).first << std::endl;
			iterator middle_to_beg = middle_to_end;
			root_erasing(middle_to_beg.base());
			while (1) {
				std::cout << "i = " << i - 1 << std::endl;
				if (--i == 0) {
					if (size_beg > size_end)
						middle_to_end = last;
					else
						middle_to_beg = first;
				}
				std::cout << "BEFORE ADD " << (*middle_to_end).first << " / / / " << (*middle_to_beg).first << std::endl;
				add(*(++middle_to_end));
				add(*(--middle_to_beg));
				std::cout << "AFTER ADD " << (*middle_to_end).first << " / / / " << (*middle_to_beg).first << std::endl;
				std::cout << (*mem_end).first << std::endl;
				if (middle_to_beg == mem_beg && middle_to_end == mem_end)
					break ;
				if (middle_to_beg == mem_beg) {
					if (--i == 0)
						add(*mem_end);
					else
						add(*(++middle_to_end));
					break ;
				}
				else if (middle_to_end == mem_end) {
					std::cout << "woop woop" << std::endl;
					if (--i == 0)
						add(*mem_beg);
					else
						add(*(--middle_to_beg));
					break ;
				}
			}
			suppress_BST(old_root);
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

		pair<iterator,bool> insert (const value_type& val) {
			return (_bst.add(val));
		}

		iterator insert (iterator position, const value_type& val) {
			return (_bst.add(val, true, position).first);	
		}

		template <class InputIterator>
 		void insert (InputIterator first, InputIterator last) {
 			_bst.add(first, last);
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


		void display_tree() {
			_bst.display_tree();
		}

		iterator find (const key_type& k) { return (_bst.find(k)); }

		size_type count (const key_type& k) const { return ((_bst.find(k) != this->end())); }

		iterator lower_bound (const key_type& k) { return (_bst.lower_bound(k)); }

		iterator upper_bound (const key_type& k) { return (_bst.upper_bound(k)); }

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

		allocator_type get_allocator() const { return (_alloc); }

	private:
		key_compare							_comp;
		allocator_type						_alloc;
		ft::BST<value_type, key_compare>	_bst;
	};


}

#endif
