#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>

namespace ft {
	template< class T, class Alloc = std::allocator<T> > class Vector {

		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference ;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef size_t size_type;
		typedef T* iterator;
		typedef const T* const_iterator;

		private:
			pointer _begin;
			size_type _capacity;
			size_type _size;
			allocator_type _allocator;

		public:
			explicit Vector(const allocator_type& alloc = allocator_type()) : _allocator(alloc), _begin(0), _capacity(0), _size(0) { }
			explicit Vector(size_type n, const value_type& val = T(), const allocator_type& alloc = allocator_type()) :
				_allocator(alloc), _begin(0), _capacity(n), _size(n) {
					_begin = _allocator.allocate(n);
					while (n--) {
						std::cout << n << val << std::endl;
						_allocator.construct(_begin + n, val);
					}
			}
			template <class InputIterator>
			Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type()) {
				size_type size = last - _begin;

				_capacity = size;
				_size = size;
				_begin = alloc.allocate(size);
				while (size--)
					alloc.construct(_begin + size, *(last--));
			}

			Vector & operator=(const Vector & rhs) {
				_capacity = rhs._capacity;
				_size = rhs._size;
				_allocator = rhs._allocator;

				size_type size = _capacity;
				_begin = _allocator.allocate(size);
				while (size--) {
					std::cout << size << *(rhs._begin + size) << std::endl;
					_allocator.construct(_begin + size, rhs._begin[size]);
				}
				return (*this);
			}

			Vector(const Vector& x) {
				*this = x;
			}

			~Vector() {
				while (_size--) {
					_allocator.destroy(_begin + _size);
				}
				_allocator.deallocate(_begin, _capacity);
			}

			iterator begin() { return (_begin); }
			const iterator begin() const { return (_begin); }

			iterator end() { return (_begin + _size); }
			const iterator end() const { return (_begin + _size); }

			size_type size() const { return (_size); }
			size_type max_size() const { return ( _allocator.max_size() ); }

			void resize (size_type n, value_type val = value_type()) {
				while ( n < _size )
					_allocator.destroy(_begin + _size--);
				if ( n > _capacity ) {
					reserve(n);
				}
				while ( n > _size++ )
					_allocator.construct(_begin + _size, val);
			}

			bool empty() const { return (!_size); }

			void reserve (size_type n) {
					pointer new_begin;
					size_type cpt = 0;

					new_begin = _allocator.allocate(n);
					while (cpt < _size) {
						_allocator.construct(new_begin + cpt, _begin[cpt]);
						++cpt;
					}
					_begin = new_begin;
					_capacity = n;
			}

			reference operator[](size_type n) { return ( *(_begin + n) ); }
			const reference operator[](size_type n) const { return ( *(_begin + n) ); }

			reference at(size_type n) {
				if (n > _size)
					throw std::out_of_range("oor");
				return ( *(_begin + n) ); 
			}

			const reference at(size_type n) const {
				if (n > _size)
					throw std::out_of_range("oor");
				return ( *(_begin + n) ); 
			}

			reference front() { return at(0); }
			const_reference front() const { return at(0); }

			reference back() { return at(_size); }
			const_reference back() const { return at(_size); }
	};
}

#endif