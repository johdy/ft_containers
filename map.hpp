#ifndef MAP_HPP
# define MAP_HPP
# include "pair.hpp"
# include <iostream>
# include "bst.hpp"
# include "reverse_iterator.hpp"
# include "utils.hpp"
namespace ft {

	template< class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
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
		size_type max_size() const { return (_bst.max_size()); }

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
				it = this->upper_bound(k);
				return (ft::pair<iterator,iterator>(it, it));
			}
			iterator itplus = it;
			return (ft::pair<iterator,iterator>(it, ++itplus));
		}

		ft::pair< const_iterator, const_iterator> equal_range (const key_type& k) const {
			const_iterator it = _bst.find(k);
			const_iterator end = _bst.end();
			if (it == end) {
				it = this->upper_bound(k);
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

	template < class Key, class T, class Compare, class Alloc >
	void swap (ft::map<Key,T,Compare,Alloc>& x, ft::map<Key,T,Compare,Alloc>& y) {
		x.swap(y);
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator== (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		if (lhs.size() != rhs.size())
			return (false);
		typename ft::map<Key,T,Compare,Alloc>::const_iterator left_it = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator right_it = rhs.begin();
		while (left_it != lhs.end() && *left_it == *right_it) {
			++left_it;
			++right_it;
		}
		return (left_it == lhs.end());
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator< (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		typename ft::map<Key,T,Compare,Alloc>::const_iterator left_it = lhs.begin();
		typename ft::map<Key,T,Compare,Alloc>::const_iterator right_it = rhs.begin();
		while (left_it != lhs.end()) {
			if (right_it == rhs.end() || (*right_it < *left_it))
				return (false);
			else if (*(left_it++) < *(right_it++))
				return (true);
		}
		return (lhs.size() != rhs.size());
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator!= (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return (!(lhs == rhs));
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator> (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return ((rhs < lhs));
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator<= (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return (!(lhs > rhs));
	}

	template < class Key, class T, class Compare, class Alloc >
	bool operator>= (const ft::map<Key,T,Compare,Alloc>& lhs, const ft::map<Key,T,Compare,Alloc>& rhs ) {
		return (!(lhs < rhs));
	}
}

#endif
