#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include "utils.hpp"
# include "iterators.hpp"
namespace ft {
	template< class T, class Alloc = std::allocator<T> > class Vector {

		public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference ;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef size_t size_type;
		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::random_access_iterator<const value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef ptrdiff_t difference_type;

		private:
			pointer _begin;
			size_type _capacity;
			size_type _size;
			allocator_type _allocator;

		public:
			explicit Vector(const allocator_type& alloc = allocator_type()) : _allocator(alloc), _begin(0), _capacity(0), _size(0) { }
			explicit Vector(size_t n, const value_type& val = T(), const allocator_type& alloc = allocator_type()) :
				_allocator(alloc), _begin(0), _capacity(n), _size(n) {
					_begin = _allocator.allocate(n);
					while (n--) {
						//std::cout << n << val << std::endl;
						_allocator.construct(_begin + n, val);
					}
			}
			template <class InputIterator>
			Vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator>::type = NULL) {
				size_type size = last - first;
				_capacity = size;
				_size = size;
				_allocator = alloc;
				_begin = _allocator.allocate(size);
				while (size--)
					_allocator.construct(_begin + size, *(first + size));
			}

			Vector & operator=(const Vector & rhs) {
				_capacity = rhs._capacity;
				_size = rhs._size;
				_allocator = rhs._allocator;

				size_type size = _capacity;
				_begin = _allocator.allocate(size);
				while (size--) {
					//std::cout << size << *(rhs._begin + size) << std::endl;
					_allocator.construct(_begin + size, rhs._begin[size]);
				}
				return (*this);
			}

			Vector(const Vector& x) {
				*this = x;
			}

			~Vector() {
				this->clear();
				_allocator.deallocate(_begin, _capacity);
			}

			iterator begin() { return (_begin); }
			const iterator begin() const { return (_begin); }

			iterator end() { return (_begin + _size); }
			const iterator end() const { return (_begin + _size); }

			reverse_iterator rbegin() { return ( reverse_iterator(end())); }
			const_reverse_iterator rbegin() const { return (reverse_iterator(end())); }

			reverse_iterator rend() { return ( reverse_iterator(begin())); }
			const_reverse_iterator rend() const { return (reverse_iterator(begin())); }

			size_type size() const { return (_size); }
			size_type max_size() const { return ( _allocator.max_size() ); }
			size_type capacity() const { return ( _capacity ); }

			void resize (size_type n, value_type val = value_type()) {
				while ( n < _size )
					_allocator.destroy(_begin + --_size);
				if ( n > _capacity ) {
					reserve(n);
				}
				while ( n > _size )
					_allocator.construct(_begin + _size++, val);
			}

			bool empty() const { return (!_size); }


			void reserve (size_type n) {
					if (n <= _capacity)
						return ;
					pointer new_begin;
					size_type cpt = 0;

					new_begin = _allocator.allocate(n);
					while (cpt < _size) {
						_allocator.construct(new_begin + cpt, _begin[cpt]);
						_allocator.destroy(_begin + cpt);
						++cpt;
					}
					_allocator.deallocate(_begin, _capacity);
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

			void clear() {
				while (_size) {
					std::cout << "oucs" << *(_begin + _size - 1) << std::endl;
					_allocator.destroy(_begin + --_size);
				}
				std::cout << "yo" << _size << std::endl;
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator>::type = NULL) {
				this->clear();
				this->reserve(last - first);
				_size = last - first;
				size_t cpt = 0;
				while (cpt < _size) {
					_allocator.construct(_begin + cpt, first.base() + cpt);
					cpt++;
				}
			}

			void assign (size_type n, const value_type& val) {
				this->clear();
				this->reserve(n);
				_size = n;
				size_t cpt = 0;
				while (cpt < _size) {
					_allocator.construct(_begin + cpt, val);
					cpt++;
				}
			}
			/*iterator insert (iterator position, const value_type& val) {

			}

			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last) {
    			if (_size + (last - first) > _capacity)
    		}*/
	};
}

#endif