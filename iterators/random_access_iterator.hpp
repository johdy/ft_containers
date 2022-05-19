#ifndef RANDOM_ACCESS_ITERATOR_HPP
# define RANDOM_ACCESS_ITERATOR_HPP
# include "iterators_utils.hpp"
namespace ft {
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
	

	template< typename T >
	class const_random_access_iterator {
	public:
		typedef typename ft::const_iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
		typedef	typename ft::const_iterator<ft::random_access_iterator_tag, T>::value_type value_type;
		typedef	typename ft::const_iterator<ft::random_access_iterator_tag, T>::difference_type difference_type;
		typedef typename ft::const_iterator<ft::random_access_iterator_tag, T>::pointer pointer;
		typedef	typename ft::const_iterator<ft::random_access_iterator_tag, T>::reference reference;

	private:
		pointer _elem;

	public:
		const_random_access_iterator() : _elem(0) { }
		const_random_access_iterator( pointer x ) { this->_elem = x; }

		template< typename U >
		const_random_access_iterator( const const_random_access_iterator<U>& other ) {
			this->_elem = other.base();
		}

		template< typename U >
		const_random_access_iterator( const random_access_iterator<U>& other ) : _elem (other.base()){
		}

		virtual ~const_random_access_iterator() {}

		const_random_access_iterator& operator= (const_random_access_iterator rhs) {
			if (*this == rhs)
				return *this;
			this->_elem = rhs.base();
			return (*this);
		}

		pointer operator->() { return &(*_elem); }

		pointer base() const { return (_elem); }
		reference operator*() const { return (*_elem); }
		const_random_access_iterator operator+ (difference_type n) const { return ( const_random_access_iterator(_elem + n) ); }
		const_random_access_iterator& operator++() { _elem++; return (*this); }
		const_random_access_iterator operator++(int) {
			const_random_access_iterator cpy = *this;
			++_elem;
			return (cpy);
		}
		const_random_access_iterator& operator+= (difference_type n) {
			*this = *this + n;
			return (*this);
		}

		const_random_access_iterator operator- (difference_type n) const { return ( const_random_access_iterator(_elem - n) ); }
		const_random_access_iterator& operator--() { _elem--; return (*this); }
		const_random_access_iterator operator--(int) {
			const_random_access_iterator cpy = *this;
			--_elem;
			return (cpy);
		}
		const_random_access_iterator& operator-= (difference_type n) {
			*this = *this - n;
			return (*this);
		}

		reference operator[] (difference_type n) const { return ( *this + n ); }
	};

	template <typename T>
	bool operator== (const const_random_access_iterator<T> lhs, const const_random_access_iterator<T> rhs) { return (lhs.base() == rhs.base()); }

	template <typename T>
	bool operator!= (const const_random_access_iterator<T> lhs, const const_random_access_iterator<T> rhs) { return (lhs.base() != rhs.base()); }

	template <typename T>
	bool operator<  (const const_random_access_iterator<T> lhs, const const_random_access_iterator<T> rhs) { return (lhs.base() < rhs.base()); }

	template <typename T>
	bool operator<= (const const_random_access_iterator<T> lhs, const const_random_access_iterator<T> rhs) { return (lhs.base() <= rhs.base()); }

	template <typename T>
	bool operator>  (const const_random_access_iterator<T> lhs, const const_random_access_iterator<T> rhs) { return (lhs.base() > rhs.base()); }

	template <typename T>
	bool operator>= (const const_random_access_iterator<T> lhs, const const_random_access_iterator<T> rhs) { return (lhs.base() >= rhs.base()); }


	template <typename T>
	std::ostream &operator<< (std::ostream& os, const const_random_access_iterator<T> lhs) {
		os << lhs.base();
		return (os);
	}


	template <typename TL, typename TR>
	bool operator== (const const_random_access_iterator<TL> lhs, const const_random_access_iterator<TR> rhs) { return (lhs.base() == rhs.base()); }

	template <typename TL, typename TR>
	bool operator!= (const const_random_access_iterator<TL> lhs, const const_random_access_iterator<TR> rhs) { return (lhs.base() != rhs.base()); }

	template <typename TL, typename TR>
	bool operator<  (const const_random_access_iterator<TL> lhs, const const_random_access_iterator<TR> rhs) { return (lhs.base() < rhs.base()); }

	template <typename TL, typename TR>
	bool operator<= (const const_random_access_iterator<TL> lhs, const const_random_access_iterator<TR> rhs) { return (lhs.base() <= rhs.base()); }

	template <typename TL, typename TR>
	bool operator>  (const const_random_access_iterator<TL> lhs, const const_random_access_iterator<TR> rhs) { return (lhs.base() > rhs.base()); }

	template <typename TL, typename TR>
	bool operator>= (const const_random_access_iterator<TL> lhs, const const_random_access_iterator<TR> rhs) { return (lhs.base() >= rhs.base()); }

	template <class T>
	const_random_access_iterator<T> operator+ (typename const_random_access_iterator<T>::difference_type n, const const_random_access_iterator<T>& it) { return (it + n); }
	template <class T>
	const_random_access_iterator<T> operator- (typename const_random_access_iterator<T>::difference_type n, const const_random_access_iterator<T>& it) { return (it - n); }
	template <class T>
	typename const_random_access_iterator<T>::difference_type operator- (const const_random_access_iterator<T>& it, const const_random_access_iterator<T>& it2) { return (it.base() - it2.base()); }
	template <class TL, class TR>
	typename const_random_access_iterator<TL>::difference_type operator- (const const_random_access_iterator<TL>& it, const const_random_access_iterator<TR>& it2) { return (it.base() - it2.base()); }


}

#endif