#ifndef REVERSE_ITERATOR_HPP
# define REVERSE_ITERATOR_HPP
# include "iterators_utils.hpp"

namespace ft {

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
		reverse_iterator& operator++() { --_elem; return (*this); }
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
		reverse_iterator& operator--() { ++_elem; return (*this); }
		reverse_iterator operator--(int) {
			reverse_iterator cpy = *this;
			++_elem;
			return (cpy);
		}
		reverse_iterator& operator-= (difference_type n) {
			*this = *this - n;
			return (*this);
		}

		pointer operator->() const {
			return (&(operator*()));
		}

		reference operator[] (difference_type n) const { return ( *this + n ); }

		bool operator== (const reverse_iterator& rhs) { return (_elem == rhs.base()); }

		bool operator!= (const reverse_iterator& rhs) { return (_elem != rhs.base()); }

		bool operator<  (const reverse_iterator& rhs) { return (_elem > rhs.base()); }

		bool operator<= (const reverse_iterator& rhs) { return (_elem >= rhs.base()); }

		bool operator>  (const reverse_iterator& rhs) { return (_elem < rhs.base()); }

		bool operator>= (const reverse_iterator& rhs) { return (_elem <= rhs.base()); }
	};

	template <class Iterator>
	reverse_iterator<Iterator> operator+ (typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& rev_it) { return (rev_it + n); }
	template <class Iterator>
	typename reverse_iterator<Iterator>::difference_type operator- (const reverse_iterator<Iterator>& rev_it, const reverse_iterator<Iterator>& rev_it2) { return (rev_it2.base() - rev_it.base()); }

	template <typename Iterator>
	std::ostream &operator<< (std::ostream& os, const reverse_iterator<Iterator> lhs) {
		os << lhs.base();
		return (os);
	}
}

#endif