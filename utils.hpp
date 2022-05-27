#ifndef UTILS_HPP
# define UTILS_HPP
# include <iostream>
# include "iterators_utils.hpp"

namespace ft {

	template<class InputIterator>
	size_t distance(InputIterator last, InputIterator first) {
		size_t size = 0;
		while (last != first) {
			++first;
			++size;
		}
		return (size);
	}

	template<class Pointer>
	Pointer leftest_from(Pointer it) {
		while (it->_left)
			it = it->_left;
		return (it);
	}

	template<class Pointer>
	Pointer rightest_from(Pointer it) {
		while (it->_right)
			it = it->_right;
		return (it);
	}

	template<class T>
	struct node {
		T *_value;
		node* _parent;
		node* _left;
		node* _right;
		bool _black;
	};

	template <class T>
	struct less {
	  bool operator() (const T& x, const T& y) const { return x < y; }
	};

	template <bool B, class T>
	struct enable_if_c {
	  typedef int type;
	};

	template <class T>
	struct enable_if_c<false, T> {};

	template <bool B, class T> 
	struct enable_if : public enable_if_c<B, T> {};

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

	/*template <>
	struct is_integral_c<char16_t> {
	  static const bool value = true;
	};

	template <>
	struct is_integral_c<char32_t> {
	  static const bool value = true;
	};*/

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
}
#endif