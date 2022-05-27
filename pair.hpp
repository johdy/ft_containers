#ifndef PAIR_HPP
# define PAIR_HPP

namespace ft {
	template<class T1, class T2> class pair {
		public:
			T1 first;
			T2 second;

			typedef  T1 first_type;
			typedef  T2 second_type;
			pair() : first(T1()) , second(T2()) { }
			pair(const T1& x, const T2& y) : first(x) , second(y) { }
			template<class U, class V>
			pair(const pair<U, V>& p) : first(p.first) , second(p.second) { }

			pair & operator=(const pair & rhs) {
				if (this != &rhs)
				{
					this->second = rhs.second;
					this->first = rhs.first;
				}
				return (*this);
			}
	};

	template <class T1, class T2>
	bool operator== (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return (lhs.first == rhs.first && lhs.second == rhs.second);
	}

	template <class T1, class T2>
	bool operator!= (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return (!(lhs == rhs));
	}

	template <class T1, class T2>
	bool operator<  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return ( lhs.first < rhs.first || (lhs.first == rhs.first && lhs.second < rhs.second) );
	}

	template <class T1, class T2>
	bool operator>=  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return (!(lhs < rhs));
	}

	template <class T1, class T2>
	bool operator>  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return (rhs < lhs);
	}

	template <class T1, class T2>
	bool operator<=  (const pair<T1,T2>& lhs, const pair<T1,T2>& rhs) {
			return (!(rhs < lhs));
	}

	template<class T1,class T2>
	ft::pair<T1,T2> make_pair(T1 x,T2 y) {
		return (ft::pair<T1,T2>(x,y));
	}
}

#endif
