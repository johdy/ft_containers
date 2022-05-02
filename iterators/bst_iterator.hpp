#ifndef BST_ITERATOR_HPP
# define BST_ITERATOR_HPP
# include "iterators_utils.hpp"
# include "../utils.hpp"

namespace ft {
	template< typename T, typename U>
	class bst_iterator {
	public:
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
		typedef	typename ft::iterator<ft::bidirectional_iterator_tag, T>::value_type value_type;
		typedef typename ft::iterator<ft::bidirectional_iterator_tag, T>::pointer pointer;
		typedef	typename ft::iterator<ft::bidirectional_iterator_tag, T>::reference reference;
		typedef	typename ft::iterator<ft::bidirectional_iterator_tag, T>::difference_type difference_type;
		typedef U under_type;

	private:
		pointer _elem;
		pointer _last_node;
		pointer _first_node;

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
		bst_iterator() : _elem(0) {
		}

		bst_iterator( pointer x ) { 
			this->_elem = x;
		}

		template< typename V, typename X >
		bst_iterator( const bst_iterator<V, X>& other ) {
			this->_elem = other.base();
		}

		virtual ~bst_iterator() {}

		bst_iterator& operator= (bst_iterator rhs) {
			if (*this == rhs)
				return *this;
			_elem = rhs.base();
			_last_node = rhs._last_node;
			_first_node = rhs._first_node;
			return (*this);
		}

		under_type* operator->() { return &(_elem->_value); }

		pointer base() const { return (_elem); }
		under_type& operator*() const { return _elem->_value; }

		bst_iterator& operator++() {
			if (_elem == NULL && _first_node) {
				_elem = _first_node;
				_last_node = NULL;
			}
			else if (_elem->_right)
				_elem = leftest_from(_elem->_right);
			else {
				_last_node = _elem;
				while (_elem->_parent) {
					if (_elem->_parent == _elem->_parent->_parent && _elem->_parent->_left != _elem) {
						_elem = NULL;
						break ;
					}
					if (_elem == _elem->_parent) {
						_elem = leftest_from(_elem);
						_last_node = NULL;
						break ;
					}
					if (_elem->_parent->_left == _elem) {
						_elem = _elem->_parent;
						_last_node = NULL;
						break ; 
					}
					_elem = _elem->_parent;
				}
			}
			return (*this);
		}

		bst_iterator operator++(int) {
			bst_iterator cpy = *this;
			++(*this);
			return (cpy);
		}

		bst_iterator& operator--() {
			if (_elem == NULL && _last_node) {
				_elem = _last_node;
				_last_node = NULL;
			}
			else if (_elem->_left)
				_elem = rightest_from(_elem->_left);
			else {
				_first_node = _elem;
				while (_elem->_parent) {
					if (_elem->_parent == _elem->_parent->_parent && _elem->_parent->_right != _elem) {
						_elem = NULL;
						break ;
					}
					if (_elem == _elem->_parent) {
						_elem = rightest_from(_elem);
						_first_node = NULL;
						break ;
					}
					if (_elem->_parent->_right == _elem) {
						_elem = _elem->_parent;
						_first_node = NULL;
						break ;
					}
					_elem = _elem->_parent;
				}
			}
			return (*this);
		}

		bst_iterator operator--(int) {
			bst_iterator cpy;

			cpy = *this;
			--(*this);
			return (cpy);
		}

	};

	template <typename T, typename U>
	bool operator== (const bst_iterator<T, U> lhs, const bst_iterator<T, U> rhs) { return (lhs.base() == rhs.base()); }
	template <typename T, typename U>
	bool operator!= (const bst_iterator<T, U> lhs, const bst_iterator<T, U> rhs) { return (lhs.base() != rhs.base()); }
}
#endif