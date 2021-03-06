#ifndef VECTOR_HPP
# define VECTOR_HPP
# include <iostream>
# include "utils.hpp"
# include "random_access_iterator.hpp"
# include "reverse_iterator.hpp"
namespace ft {
	template< class T, class Alloc = std::allocator<T> > class vector {

		public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference ;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef size_t size_type;
		typedef ft::random_access_iterator<value_type> iterator;
		typedef ft::const_random_access_iterator<value_type> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef std::ptrdiff_t difference_type;

		private:
			pointer _begin;
			size_type _capacity;
			size_type _size;
			allocator_type _allocator;


			void copy_up_until(iterator position, pointer &new_begin) {
				iterator it(this->begin());

				while (it != position) {
					--position;
					_allocator.construct(new_begin + (position - it), _begin[position - it]);
					_allocator.destroy(_begin + (position - it));
				}
				_allocator.deallocate(_begin, _capacity);
				_begin = new_begin;
			}

			size_t copy_end(iterator position, pointer &begin, size_t nb_insert, bool erase = 0) {
				iterator end = this->end();
				size_t cpt = _size - 1;

				while (position + nb_insert != end) {
					_allocator.construct(begin + cpt, *(_begin + cpt - nb_insert));
					if (erase)
						_allocator.destroy(_begin + cpt - nb_insert);
					--cpt;
					--end;
				}
				return (cpt);
			}

		public:
			explicit vector(const allocator_type& alloc = allocator_type()) : _begin(0), _capacity(0), _size(0), _allocator(alloc) {
			}

			explicit vector(size_t n, const value_type& val = T(), const allocator_type& alloc = allocator_type()) :
				_begin(0), _capacity(n), _size(n), _allocator(alloc) {
					if (!n)
						return ;
					_begin = _allocator.allocate(n);
					while (n--) {
						_allocator.construct(_begin + n, val);
					}
			}
			template <class InputIterator>
			vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(), typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator>::type = 0) {
				_size = ft::distance<InputIterator>(last, first);
				_capacity = _size;
				_allocator = alloc;
				if (!_size)
					return ;
				_begin = _allocator.allocate(_size);
				size_type cpt = 0;
				while (cpt < _size) {
					_allocator.construct(_begin + cpt, *(first++));
					++cpt;
				}
			}

			vector & operator=(const vector & rhs) {
				if (*this == rhs)
					return (*this);

				this->clear();
				if (_capacity < rhs._capacity)
					this->reserve(rhs._capacity);
				else if (!rhs._capacity)
					_allocator.deallocate(_begin, _capacity);
				_capacity = rhs._capacity;
				_size = rhs._size;
				_allocator = rhs._allocator;

				size_type size = _size;
				while (size--) {
					_allocator.construct(_begin + size, rhs._begin[size]);
				}
				return (*this);
			}

			vector(const vector& x) : _capacity(0), _size(0){
				*this = x;
			}

			~vector() {
				if (!_capacity)
					return ;
				size_type cap_tmp = _capacity;
				while (_size)
					_allocator.destroy(_begin + --_size);
				_size = 0;
				_allocator.deallocate(_begin, cap_tmp);
			}

			iterator begin() { return (_begin); }
			const_iterator begin() const { return (_begin); }

			iterator end() { return (_begin + _size); }
			const_iterator end() const { return (_begin + _size); }

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
					reserve((n > _size * 2) ? n : _size * 2);
				}
				while ( n > _size )
					_allocator.construct(_begin + _size++, val);
			}

			bool empty() const { return (!_size); }


			void reserve (size_type n) {
					if (n <= _capacity)
						return ;
					if (n > this->max_size())
						throw (std::length_error("vector::reserve"));
					pointer new_begin;
					size_type cpt = 0;

					new_begin = _allocator.allocate(n);
					while (cpt < _size) {
						_allocator.construct(new_begin + cpt, _begin[cpt]);
						_allocator.destroy(_begin + cpt);
						++cpt;
					}
					if (_capacity && _begin)
						_allocator.deallocate(_begin, _capacity);
					_begin = new_begin;
					_capacity = n;
			}

			reference operator[](size_type n) { return ( *(_begin + n) ); }
			const reference operator[](size_type n) const { return ( *(_begin + n) ); }

			reference at(size_type n) {
				if (n >= _size)
					throw std::out_of_range("vector::range_check: n >= this->size()");
				return ( *(_begin + n) ); 
			}

			const reference at(size_type n) const {
				if (n >= _size)
					throw std::out_of_range("vector::range_check: n >= this->size()");
				return ( *(_begin + n) ); 
			}

			reference front() { return at(0); }
			const_reference front() const { return at(0); }

			reference back() { return at(_size - 1); }
			const_reference back() const { return at(_size - 1); }

			void clear() {
				while (_size)
					_allocator.destroy(_begin + --_size);
			}

			template <class InputIterator>
			void assign (InputIterator first, InputIterator last, typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator>::type = 0) {
				this->clear();
				size_t dist = ft::distance<InputIterator>(last, first);
				this->reserve(dist);
				_size = dist;
				size_t cpt = 0;
				while (cpt < _size) {
					_allocator.construct(_begin + cpt, *(first++));
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

			void push_back (const value_type& val) {
				if (!_capacity)
					this->reserve(1);
				else if (_size == _capacity)
					this->reserve(_size * 2);
				_allocator.construct(_begin + _size++, val);
			}

			void pop_back() {
				_allocator.destroy(_begin + --_size);
			}

			iterator insert (iterator position, const value_type& val) {
				pointer new_begin;
				size_t loc;

				if (_size++ == _capacity) {
					new_begin = _allocator.allocate(_capacity * 2);
					loc = copy_end(position, new_begin, 1, 1);
					copy_up_until(position, new_begin);
					_capacity = _capacity * 2;
				}
				else
					loc = copy_end(position, _begin, 1);
				_allocator.construct(_begin + loc, val);
				return (this->begin() + loc);
			}

			void insert (iterator position, size_type n, const value_type& val) {
				pointer new_begin;
				size_t loc;
				size_t old_size = _size;

				if (n == 0)
					return ;
				_size += n;
				if (_size > _capacity) {
					_capacity = (_size > old_size * 2) ? _size : old_size * 2;
					new_begin = _allocator.allocate(_capacity);
					loc = copy_end(position, new_begin, n, 1);
					copy_up_until(position, new_begin);
				}
				else
					loc = copy_end(position, _begin, n);
				while (n)
					_allocator.construct(_begin + loc - --n, val);
			}

			template <class InputIterator>
    		void insert (iterator position, InputIterator first, InputIterator last,
    					typename ft::enable_if< !ft::is_integral<InputIterator>::value, InputIterator>::type = 0) {
				pointer new_begin;
				size_t loc;
				size_t old_size = _size;
				size_t dist = ft::distance<InputIterator>(last, first);
				if (dist == 0)
					return ;
				_size += dist;
				if (_size > _capacity) {
					_capacity = (_size > old_size * 2) ? _size : old_size * 2;
					new_begin = _allocator.allocate(_capacity);
					loc = copy_end(position, new_begin, dist, 1);
					copy_up_until(position, new_begin);
				}
				else
					loc = copy_end(position, _begin, dist);
				while (dist) {
					_allocator.construct(_begin + loc - dist + 1, *first);
					++first;
					--dist;
				}
    		}

    		iterator erase (iterator position) {
    			iterator vec_end(this->end());
    			iterator head(position);

    			if (position == vec_end)
    				return (position);
    			while (++head != vec_end) {
    				_allocator.destroy(&(*head) - 1);
    				_allocator.construct(&(*head) - 1, *head);
    			}
    			_allocator.destroy(_begin + --_size);
    			return (position);
    		}

    		iterator erase (iterator first, iterator last) {
    			size_t i = 0;
    			iterator vec_end(this->end());

    			if (first == vec_end)
    				return (first);
    			while ((last + i) != vec_end) {
    				_allocator.destroy(&(*first) + i);
    				_allocator.construct(&(*first) + i, *(last + i));
    				++i;
    			}
    			this->resize(_size - (last - first));
    			return (first);
    		}

    		void swap (vector& x) {
				pointer tmp_begin = _begin;
				size_type tmp_cap = _capacity;
				size_type tmp_size = _size;
				allocator_type tmp_alloc = _allocator;

				_begin = x._begin;
				_capacity = x._capacity;
				_size = x._size;
				_allocator = x._allocator;

				x._allocator = tmp_alloc;
				x._size = tmp_size;
				x._capacity =  tmp_cap;
				x._begin = tmp_begin;
    		}

    		allocator_type get_allocator() const { return (_allocator); }
	};

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y) {
		x.swap(y);
	}

	template <class T, class Alloc>
	bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		if (lhs.size() != rhs.size())
			return (false);
		size_t i = 0;
		while (i != lhs.size() && *(lhs.begin() + i) == *(rhs.begin() + i))
			++i;
		return (i == lhs.size());
	}

	template <class T, class Alloc>
	bool operator< (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		size_t i = 0;
		while (i != lhs.size()) {
			if (i == rhs.size() || *(rhs.begin() + i) < *(lhs.begin() + i))
				return (false);
			else if (*(lhs.begin() + i) < *(rhs.begin() + i))
				return (true);
			++i;
		}
		return (lhs.size() != rhs.size());
	}

	template <class T, class Alloc>
	bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return (!(lhs == rhs));
	}

	template <class T, class Alloc>
	bool operator> (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return ((rhs < lhs));
	}

	template <class T, class Alloc>
	bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return (!(lhs > rhs));
	}

	template <class T, class Alloc>
	bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs) {
		return (!(lhs < rhs));
	}
}

#endif