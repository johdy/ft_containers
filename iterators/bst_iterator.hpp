#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP
# include "iterators_utils.hpp"
# include "../utils.hpp"

namespace ft {
	template< typename T >
	class bst_iterator {
	public:
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
		typedef	typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
		typedef	typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference reference;
		typedef	typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type difference_type;

	private:
		pointer _elem;

		pointer leftest_from(pointer it) {
			while (it->_left)
				it = it->_left;
			return (it);
		}

		pointer rightest_from(pointer it) {
			while (it->_right)
				it = it->_right;
			return (it);
		}

	public:
		bst_iterator() : _elem(0) { }
		bst_iterator( pointer x ) { this->_elem = x; }

		template< typename U >
		bst_iterator( const bst_iterator<U>& other ) {
			this->_elem = other.base();
		}

		virtual ~bst_iterator() {}

		bst_iterator& operator= (bst_iterator rhs) {
			if (*this == rhs)
				return *this;
			this->_elem = rhs.base();
			return (*this);
		}

		pointer operator->() { return &(*_elem); }

		pointer base() const { return (_elem); }
		reference operator*() const { return (*_elem); }

		bst_iterator& operator++() {
			if (_elem->_right)
				_elem = leftest_from(_elem->_right);
			else {
				while (_elem->_parent) {
					if (_elem == _elem->_parent) {
						_elem = leftest_from(_elem);
						break ;
					}
					if (_elem->_parent->_left == _elem) {
						_elem = _elem->_parent;
						break ; 
					}
					_elem = _elem->_parent;
				}
			}
			return (*this);
		}

		bst_iterator operator++(int) {
			bst_iterator cpy = *this;
			++_elem;
			return (cpy);
		}

		bst_iterator& operator--() {
			if (_elem->_left)
				_elem = rightest_from(_elem->_left);
			else {
				while (_elem->_parent) {
					if (_elem == _elem->_parent) {
						_elem = rightest_from(_elem);
						break ;
					}
					if (_elem->_parent->_right == _elem) {
						_elem = _elem->_parent;
						break ;
					}
					_elem = _elem->_parent;
				}
			}
			return (*this);
		}

		bst_iterator operator--(int) {
			bst_iterator cpy = *this;
			--_elem;
			return (cpy);
		}

	};

	template <typename T>
	bool operator== (const bst_iterator<T> lhs, const bst_iterator<T> rhs) { return (lhs.base() == rhs.base()); }
}
#endif