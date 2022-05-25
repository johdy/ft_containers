#ifndef ITERATORS_UTILS_HPP
# define ITERATORS_UTILS_HPP

namespace ft {

	class random_access_iterator_tag {};

	class bidirectional_iterator_tag {};

	template <class Category, class T, class Distance = std::ptrdiff_t,
	class Pointer = T*, class Reference = T&>
	struct iterator {
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
 	};

 	template <class Category, class T, class Distance = std::ptrdiff_t,
	class Pointer = T*, class Reference = T&>
	struct const_iterator {
		typedef T				value_type;
		typedef Distance		difference_type;
		typedef Pointer	pointer;
		typedef Reference	reference;
		typedef Category		iterator_category;
 	};

	template<class Iter>
	struct iterator_traits {
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::reference reference;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::iterator_category iterator_category;
	};

}

#endif