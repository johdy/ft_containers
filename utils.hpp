#ifndef UTILS_HPP
# define UTILS_HPP
# include <iostream>

namespace ft {

	template<class T>
	struct node {
		T *_value;
		node* _parent;
		node* _left;
		node* _right;
	};

	template <class T>
	struct less {
	  bool operator() (const T& x, const T& y) const { return x < y; }
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
}
#endif