#ifndef ITERATORS_HPP
# define ITERATORS_HPP
# include "utils.hpp"
# include "map.hpp"
namespace ft {

	class random_access_iterator_tag {};

	class bst_iterator_tag {};

	template <class Category, class T, class Distance = ptrdiff_t,
	class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
 	};

	template< typename T >
	class random_access_iterator {
	public:
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
		typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::value_type value_type;
		typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::iterator<ft::random_access_iterator_tag, T>::pointer pointer;
		typedef	typename ft::iterator<ft::random_access_iterator_tag, T>::reference reference;

	private:
		pointer _elem;

	public:
		random_access_iterator() : _elem(0) { }
		random_access_iterator( pointer x ) { this->_elem = x; }

		template< typename U >
		random_access_iterator( const random_access_iterator<U>& other ) {
			this->_elem = other.base();
		}

		virtual ~random_access_iterator() {}

		random_access_iterator& operator= (random_access_iterator rhs) {
			if (*this == rhs)
				return *this;
			this->_elem = rhs.base();
			return (*this);
		}

		pointer operator->() { return &(*_elem); }

		pointer base() const { return (_elem); }
		reference operator*() const { return (*_elem); }
		random_access_iterator operator+ (difference_type n) const { return ( random_access_iterator(_elem + n) ); }
		random_access_iterator& operator++() { _elem++; return (*this); }
		random_access_iterator operator++(int) {
			random_access_iterator cpy = *this;
			++_elem;
			return (cpy);
		}
		random_access_iterator& operator+= (difference_type n) {
			*this = *this + n;
			return (*this);
		}

		random_access_iterator operator- (difference_type n) const { return ( random_access_iterator(_elem - n) ); }
		random_access_iterator& operator--() { _elem--; return (*this); }
		random_access_iterator operator--(int) {
			random_access_iterator cpy = *this;
			--_elem;
			return (cpy);
		}
		random_access_iterator& operator-= (difference_type n) {
			*this = *this - n;
			return (*this);
		}

		reference operator[] (difference_type n) const { return ( *this + n ); }
	};

	template <typename T>
	bool operator== (const random_access_iterator<T> lhs, const random_access_iterator<T> rhs) { return (lhs.base() == rhs.base()); }

	template <typename T>
	bool operator!= (const random_access_iterator<T> lhs, const random_access_iterator<T> rhs) { return (lhs.base() != rhs.base()); }

	template <typename T>
	bool operator<  (const random_access_iterator<T> lhs, const random_access_iterator<T> rhs) { return (lhs.base() < rhs.base()); }

	template <typename T>
	bool operator<= (const random_access_iterator<T> lhs, const random_access_iterator<T> rhs) { return (lhs.base() <= rhs.base()); }

	template <typename T>
	bool operator>  (const random_access_iterator<T> lhs, const random_access_iterator<T> rhs) { return (lhs.base() > rhs.base()); }

	template <typename T>
	bool operator>= (const random_access_iterator<T> lhs, const random_access_iterator<T> rhs) { return (lhs.base() >= rhs.base()); }


	template <typename T>
	std::ostream &operator<< (std::ostream& os, const random_access_iterator<T> lhs) {
		os << lhs.base();
		return (os);
	}


	template <typename TL, typename TR>
	bool operator== (const random_access_iterator<TL> lhs, const random_access_iterator<TR> rhs) { return (lhs.base() == rhs.base()); }

	template <typename TL, typename TR>
	bool operator!= (const random_access_iterator<TL> lhs, const random_access_iterator<TR> rhs) { return (lhs.base() != rhs.base()); }

	template <typename TL, typename TR>
	bool operator<  (const random_access_iterator<TL> lhs, const random_access_iterator<TR> rhs) { return (lhs.base() < rhs.base()); }

	template <typename TL, typename TR>
	bool operator<= (const random_access_iterator<TL> lhs, const random_access_iterator<TR> rhs) { return (lhs.base() <= rhs.base()); }

	template <typename TL, typename TR>
	bool operator>  (const random_access_iterator<TL> lhs, const random_access_iterator<TR> rhs) { return (lhs.base() > rhs.base()); }

	template <typename TL, typename TR>
	bool operator>= (const random_access_iterator<TL> lhs, const random_access_iterator<TR> rhs) { return (lhs.base() >= rhs.base()); }

	template <class T>
	random_access_iterator<T> operator+ (typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& it) { return (it + n); }
	template <class T>
	random_access_iterator<T> operator- (typename random_access_iterator<T>::difference_type n, const random_access_iterator<T>& it) { return (it - n); }
	template <class T>
	typename random_access_iterator<T>::difference_type operator- (const random_access_iterator<T>& it, const random_access_iterator<T>& it2) { return (it.base() - it2.base()); }
	template <class TL, class TR>
	typename random_access_iterator<TL>::difference_type operator- (const random_access_iterator<TL>& it, const random_access_iterator<TR>& it2) { return (it.base() - it2.base()); }



	template< class Iter >
	class reverse_iterator {
	public:
		typedef Iter iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef	typename ft::iterator_traits<Iter>::value_type value_type;
		typedef	typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef	typename ft::iterator_traits<Iter>::reference reference;

	private:
		iterator_type _elem;

	public:
		reverse_iterator() : _elem(0) { }
		explicit reverse_iterator( iterator_type x ) { this->_elem = x; }

		template< class U >
		reverse_iterator( const reverse_iterator<U>& other ) {
			this->_elem = other.base();
		}


		iterator_type base() const { return (_elem); }
		reference operator*() const {
			iterator_type cpy = _elem;
			return (*(--cpy));
		}
		reverse_iterator operator+ (difference_type n) const { return ( reverse_iterator(_elem - n) ); }
		reverse_iterator& operator++() { _elem--; return (*this); }
		reverse_iterator operator++(int) {
			reverse_iterator cpy = *this;
			--_elem;
			return (cpy);
		}
		reverse_iterator& operator+= (difference_type n) {
			*this = *this + n;
			return (*this);
		}

		reverse_iterator operator- (difference_type n) const { return ( reverse_iterator(_elem + n) ); }
		reverse_iterator& operator--() { _elem++; return (*this); }
		reverse_iterator operator--(int) {
			reverse_iterator cpy = *this;
			++_elem;
			return (cpy);
		}
		reverse_iterator& operator-= (difference_type n) {
			*this = *this - n;
			return (*this);
		}

		pointer operator->() const { return &(*this); }

		reference operator[] (difference_type n) const { return ( *this + n ); }
	};

	template <class Iterator>
	bool operator== (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() == rhs.base()); }

	template <class Iterator>
	bool operator!= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() != rhs.base()); }

	template <class Iterator>
	bool operator<  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() > rhs.base()); }

	template <class Iterator>
	bool operator<= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() >= rhs.base()); }

	template <class Iterator>
	bool operator>  (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() < rhs.base()); }

	template <class Iterator>
	bool operator>= (const reverse_iterator<Iterator>& lhs, const reverse_iterator<Iterator>& rhs) { return (lhs.base() <= rhs.base()); }

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& rev_it, const reverse_iterator<Iterator>& rev_it2) { return (rev_it2.base() - rev_it.base()); }

	template <typename Iterator>
	std::ostream &operator<< (std::ostream& os, const reverse_iterator<Iterator> lhs) {
		os << lhs.base();
		return (os);
	}

	template< typename T >
	class bst_iterator {
	public:
		typedef typename ft::iterator<ft::bst_iterator_tag, T, ft::node<T>*>::iterator_category iterator_category;
		typedef	typename ft::iterator<ft::bst_iterator_tag, T, ft::node<T>*>::value_type value_type;
		typedef typename ft::node<T>* pointer;
		typedef	typename ft::iterator<ft::bst_iterator_tag, T, ft::node<T>*>::reference reference;

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
				_elem = _elem->_right;
			else {
				while (_elem->_parent) {
					if (_elem == _elem->_parent) {
						_elem = leftest_from(_elem);
						break ;
					}
					else if (_elem->_parent->_right != _elem) {
						_elem = leftest_from(_elem->_parent->_right);
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
				_elem = _elem->_left;
			else {
				while (_elem->_parent) {
					if (_elem == _elem->_parent) {
						_elem = rightest_from(_elem);
						break ;
					}
					if (_elem->_parent->_right != _elem) {
						_elem = rightest_from(_elem->_parent->_left);
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