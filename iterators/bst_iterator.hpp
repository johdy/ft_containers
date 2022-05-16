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
		typedef typename ft::node<T>* node_pointer;

	private:
		node_pointer _elem;

	public:
		bst_iterator() : _elem(0) {
		}

		bst_iterator( node_pointer x ) { 
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
			return (*this);
		}

		pointer operator->() { return _elem->_value; }

		node_pointer base() const { return (_elem); }
		reference operator*() const { return *(_elem->_value); }

		bst_iterator& operator++() {
			if (_elem->_right)
				_elem = leftest_from(_elem->_right);
			else {
				while (_elem->_parent) {
					if (_elem->_parent->_left == _elem) {
						_elem = _elem->_parent;
						break ; 
					}
					if (_elem->_parent == NULL) {
						_elem = NULL;
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
			if (_elem->_left)
				_elem = rightest_from(_elem->_left);
			else {
				while (_elem->_parent) {
					if (_elem->_parent->_right == _elem) {
						_elem = _elem->_parent;
						break ;
					}
					if (_elem->_parent == NULL) {
						_elem = NULL;
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
		bool operator==(bst_iterator& rhs) { return (_elem == rhs.base()); }

		bool operator!=(bst_iterator& rhs) { return (_elem != rhs.base()); }
	};

	template <typename T, typename U>
	bool operator== (const bst_iterator<T, U> lhs, const bst_iterator<T, U> rhs) { return (lhs.base() == rhs.base()); }
	template <typename T, typename U>
	bool operator!= (const bst_iterator<T, U> lhs, const bst_iterator<T, U> rhs) { return (lhs.base() != rhs.base()); }
}
#endif