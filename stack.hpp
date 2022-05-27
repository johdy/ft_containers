#ifndef STACK_HPP
# define STACK_HPP
# include "vector.hpp"

namespace ft {
	template< class T, class Container = ft::vector<T> > class stack {
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

	private:
		container_type ct;

	public:
		explicit stack (const container_type& ctnr = container_type()) : ct(ctnr) {}

		bool empty() const { return (ct.empty()); }
		size_type size() const { return (ct.size()); }
		value_type& top() { return (ct.back()); }
		const value_type& top() const { return (ct.back()); }
		void push (const value_type& val) { ct.push_back(val); }
		void pop() { ct.pop_back(); }

	template <class Tn, class ContainerN>
	friend bool operator== (const ft::stack<Tn,ContainerN>&, const ft::stack<Tn,ContainerN>&);
	template <class Tn, class ContainerN>
	friend bool operator!= (const ft::stack<Tn,ContainerN>&, const ft::stack<Tn,ContainerN>&);
	template <class Tn, class ContainerN>
	friend bool operator< (const ft::stack<Tn,ContainerN>&, const ft::stack<Tn,ContainerN>&);
	template <class Tn, class ContainerN>
	friend bool operator<= (const ft::stack<Tn,ContainerN>&, const ft::stack<Tn,ContainerN>&);
	template <class Tn, class ContainerN>
	friend bool operator> (const ft::stack<Tn,ContainerN>&, const ft::stack<Tn,ContainerN>&);
	template <class Tn, class ContainerN>
	friend bool operator>= (const ft::stack<Tn,ContainerN>&, const ft::stack<Tn,ContainerN>&);
};

	template <class T, class Container>
	bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.ct == rhs.ct);
	}

	template <class T, class Container>
	bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.ct != rhs.ct);
	}

	template <class T, class Container>
	bool operator< (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.ct < rhs.ct);
	}

	template <class T, class Container>
	bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.ct <= rhs.ct);
	}

	template <class T, class Container>
	bool operator> (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.ct > rhs.ct);
	}

	template <class T, class Container>
	bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs) {
		return (lhs.ct >= rhs.ct);
	}
}

#endif