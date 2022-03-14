#ifndef UTILS_HPP
# define UTILS_HPP
# include <iostream>

namespace ft {

	template<class Iter>
	struct iterator_traits {
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::reference reference;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <bool B, class T>
	struct enable_if_c {
	  typedef T type;
	};

	template <class T>
	struct enable_if_c<false, T> {};

	template <bool c, class T> 
	struct enable_if : public enable_if_c<c, T> {};

	template <class T>
	struct is_integral_c {
		static const bool value = false;
	};

	template <>
	struct is_integral_c<bool> {
	  static const bool value = true;
	};

	template <>
	struct is_integral_c<char> {
	  static const bool value = true;
	};

	template <>
	struct is_integral_c<char16_t> {
	  static const bool value = true;
	};

	template <>
	struct is_integral_c<char32_t> {
	  static const bool value = true;
	};

	template <>
	struct is_integral_c<int> {
	  static const bool value = true;
	};

	template <>
	struct is_integral_c<wchar_t> {
	  static const bool value = true;
	};

	template <>
	struct is_integral_c<short> {
	  static const bool value = true;
	};

	template <>
	struct is_integral_c<long> {
	  static const bool value = true;
	};

	template <>
	struct is_integral_c<long long> {
	  static const bool value = true;
	};

	template <class T> 
	struct is_integral : public is_integral_c<T> {};

	template< class T >
	class random_access_iterator {
		//typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef T* value_type;
		typedef typename T::difference_type difference_type;
		typedef T** pointer;
		typedef T reference;
	};



	template< class Iter >
	class reverse_iterator {
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
		reverse_iterator& operator++() { _elem--; }
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
		reverse_iterator& operator--() { _elem++; }
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
	reverse_iterator<Iterator> operator- (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return (rev_it - n); }
}
#endif