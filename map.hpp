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

		void	add_range_except(iterator first, iterator last_included, iterator avoid) {
    		iterator middle = first;
    		size_t size = 0;

			std::cout << first->first << "+" << last_included->first << std::endl;
    		while (middle != last_included) {
    			++size;
    			++middle;
    		}
    		if (size == 0)
    			return ;
    		size = size / 2 + 1;
			std::cout << size << std::endl;
    		while (--size)
    			--middle;
    		if (middle != avoid)
    			this->add(*middle);
    		iterator it = middle;
			std::cout << it->first << "-" << middle->first << std::endl;
	  		while (it-- != first) {
    			if (it != avoid)
    				this->add(*it);
    		}
	   		it = middle;
    		while (it++ != last_included) {
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
			std::cout << _root << std::endl;
    		_node_alloc.destroy(_end);
			_node_alloc.deallocate(_end, 1);
			std::cout << _end << std::endl;
    	}

    	void clear() {
    		if (_root)
    			suppress_BST(_root);
			_node_alloc.destroy(_end);
			_node_alloc.deallocate(_end, 1);
			this->initialize();
    	}

    	void initialize(const key_compare comp = key_compare()) {
			_node_alloc = node_alloc();
    		_root = alloc_new_node();
    		_comp = comp;
    		_size = 0;
			_end = alloc_new_node();
			_root->_right = _end;
			_end->_parent = _root;
    	}

		iterator begin() const { 
			Node *head = _root;
			while (head->_left)
				head = head->_left;
			return (iterator(head));
		}

		iterator end() const { 
			return (iterator(_end));
		}

    	void display_recursif(Node *node_to_disp, int level) {
    		if (node_to_disp->_left) {
    			display_recursif(node_to_disp->_left, level + 1);
    		}
    		if (node_to_disp->_right) {
    			display_recursif(node_to_disp->_right, level + 1);
    		}
			if (node_to_disp == _end)
				return ;
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
    		while (next != NULL && next != _end) {
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
			_root->_right = _end;
			_end->_parent = _root;
			return;
		}

		void erase(iterator position) {
			Node *suppr_node = position.base();
			Node *determine_range = suppr_node;

			if (suppr_node == _root) {
				iterator beg = begin();
				iterator en = --end();
				std::cout << this->end().base() << std::endl;
				std::cout << this->end().base()->_parent << std::endl;
				std::cout << en.base() << std::endl;
				std::cout << position.base() << std::endl;
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
			while (determine_range->_right && determine_range->_right != _end)
				determine_range = determine_range->_right;
			if (determine_range->_right == _end) {
				std::cout << "et pourtant " << suppr_node->_parent << std::endl;
				suppr_node->_parent->_right = _end;
				_end->_parent = suppr_node->_parent;
				std::cout << "et pourtant " << _end->_parent << std::endl;
			}
			iterator last(determine_range);
			this->add_range_except(first, last, position);
			this->suppress_BST(suppr_node);
		}

		size_type erase (const key_type& k) {
			iterator locate = this->find(k);

			if (locate == this->end()) {
				return (0);
			}
			this->erase(locate);
			return (1);
		}

		iterator leftest_from(Node *nd) {
			std::cout << "oy" << std::endl;
			while (nd->_left)
				nd = nd->_left;
			return (nd);
		}

		iterator rightest_from(Node *nd) {
			while (nd->_right)
				nd = nd->_right;
			return (nd);
		}

		bool is_parent(Node *nd, Node *parent_candidate) {
			while (nd->_parent != nd) {
				if (nd == parent_candidate)
					return (true);
				nd = nd->_parent;;
			}
			return (false);
		}

		void erase (iterator first, iterator last) {
			iterator head = last;
			key_type stop_val = first->first;
			while (1) {
				if ((--head)->first == stop_val) 
					break ;
				std::cout << head->first << std::endl;

				this->erase(head);
				head = last;
			}
			std::cout << "nonono" << std::endl;
			this->erase(head);
		}
		/*void erase (iterator first, iterator last) {
			Node *lower_to_readd = first.base()->_left;
			Node *greater_to_readd = (--last).base()->_right;
			Node *greatest_parent = first.base();
			Node *greatest_parent_mem = greatest_parent;
			Node *greatest_parent_it = greatest_parent_mem;

			while (first != last) {
				std::cout << first->first << std::endl;
				while (is_parent(first.base(), greatest_parent) && first != last) {
					++first;
				}
				if (greatest_parent->_parent->_left == greatest_parent)
					greatest_parent->_parent->_left = NULL;
				else
					greatest_parent->_parent->_right = NULL;
				greatest_parent->_parent = NULL;
				if (greatest_parent != greatest_parent_mem) {
					std::cout << "im " << greatest_parent_it->_parent << std::endl;
					greatest_parent_it = greatest_parent_mem;
					while (greatest_parent_it->_parent) {
						greatest_parent_it = greatest_parent_it->_parent;
					}
					greatest_parent_it->_parent = greatest_parent;
				}
				greatest_parent = first.base();
			}
			std::cout << lower_to_readd << "//" << greater_to_readd << std::endl;
			if (lower_to_readd)
				this->add_range(leftest_from(lower_to_readd), rightet_from(lower_to_readd));
			if (greater_to_readd)
				this->add_range(leftest_from(greater_to_readd), rightest_from(greater_to_readd));
			std::cout << "ok" << std::endl;
			while (greatest_parent_mem) {
				greatest_parent_it = greatest_parent_mem->_parent;
				this->suppress_BST(greatest_parent_mem);
				greatest_parent_mem = greatest_parent_it;
			}
		}*/
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
