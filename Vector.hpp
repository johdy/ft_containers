#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>

namespace ft {
	template< class T, class Alloc = std::allocator<T> > class Vector {
		private:
			//typename Alloc::pointer begin;
			//typename Alloc::pointer finish;
			//typename Alloc::pointer end;
			T *begin;
			T *finish;
			T *end;
			Alloc alloc;

		public:
			explicit Vector(const Alloc& alloc = Alloc()) : alloc(alloc), begin(0), finish(0), end(0) { }
			explicit Vector(typename Alloc::size_type n, const T& val = T(), const Alloc& allocor = Alloc()) :
				alloc(allocor), begin(0), finish(0), end(0) {
					begin = alloc.allocate(n);
					finish = begin + n;
					end = finish + 1;
					while (n--) {
						std::cout << n << val << std::endl;
						alloc.construct(begin + n, val);
					}
			}
	};
}

#endif