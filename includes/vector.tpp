#ifndef VECTOR_TPP
#define VECTOR_TPP
#include <iostream>
#include "random_access_iterator.tpp"
#include "iterator.tpp"
#include "type_traits.tpp"
#include "algorithm.tpp"

namespace ft
{
	template <class T, typename Alloc>
	class vector_base
	{
	public:
		typedef Alloc allocator_type;
		typedef typename Alloc::template rebind<T>::other Tp_alloc_type;
		typedef typename Tp_alloc_type::pointer pointer;
		vector_base(){};
		vector_base(const allocator_type &alloc)
			: _impl(alloc){};

	protected:
		class vector_impl : public Tp_alloc_type
		{
		public:
			pointer _data;
			pointer _end_data;
			pointer _end_of_storage;
			vector_impl()
				: Tp_alloc_type(), _data(), _end_data(), _end_of_storage()
			{
			}
			vector_impl(Tp_alloc_type const &alloc)
				: Tp_alloc_type(alloc),
				  _data(),
				  _end_data(),
				  _end_of_storage()
			{
			}
		};
		vector_impl _impl;
	};

	template <class T, class Alloc = std::allocator<T> >
	class vector : public vector_base<T, Alloc>
	{
	public:
		typedef vector_base<T, Alloc>
			Base;
		typedef T value_type;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef Alloc allocator_type;
		typedef typename vector_base<T, Alloc>::Tp_alloc_type Tp_alloc_type;
		typedef typename Tp_alloc_type::reference reference;
		typedef typename Tp_alloc_type::const_reference const_reference;
		typedef typename Base::pointer pointer;
		typedef typename Tp_alloc_type::const_pointer const_pointer;
		typedef random_access_iterator<pointer, vector> iterator;
		typedef random_access_iterator<const_pointer, vector> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

		explicit vector(const allocator_type &alloc = allocator_type())
			: Base(alloc)
		{
		}
		
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: Base(alloc)
		{
			_impl._data = _impl.allocate(n);
			_impl._end_data = _impl._data;
			while (n--)
				_impl.construct(_impl._end_data++, val);
			_impl._end_of_storage = _impl._end_data;
		}
		
		template <class InputIterator>
		vector(InputIterator first,
			   typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last,
			   const allocator_type &alloc = allocator_type())
			: Base(alloc)
		{
			difference_type n = ft::distance(first, last);
			_impl._data = _impl.allocate(n);
			_impl._end_data = _impl._data;
			while (n--)
				::new (_impl._end_data++) value_type(*first++);
			_impl._end_of_storage = _impl._end_data;
		}

		vector(const vector &x)
			: Base(x._impl)
		{
			size_type n = x.size();
			_impl._data = _impl.allocate(n);
			_impl._end_data = _impl._data;
			for (const_iterator it = x.begin(); it != x.end(); ++it)
				::new (_impl._end_data++) value_type(*it);
			_impl._end_of_storage = _impl._end_data;
		}

		~vector()
		{
			for (pointer p = _impl._data; p != _impl._end_data; ++p)
				_impl.destroy(p);
			_impl.deallocate(_impl._data, capacity());
		}

		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				assign(x.begin(), x.end());
			}
			return (*this);
		}

		iterator begin()
		{
			return (iterator(_impl._data));
		}

		const_iterator begin() const
		{
			return (const_iterator(_impl._data));
		}

		iterator end()
		{
			return (iterator(_impl._end_data));
		}

		const_iterator end() const
		{
			return (const_iterator(_impl._end_data));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		size_type size() const
		{
			return (size_type(this->_impl._end_data - this->_impl._data));
		}

		size_type max_size() const
		{
			return (_impl.max_size());
		}

		void resize(size_type n, value_type val = value_type())
		{
			size_type size = this->size();
			if (n < size)
			{
				while (size-- != n)
				{
					_impl.destroy(_impl._end_data--);
				}
			}
			else if (n > size)
			{
				if (n > capacity())
					reserve(std::max(n * 2, size_type(1)));
				while (size++ < n)
					*_impl._end_data++ = val;
			}
		}

		size_type capacity() const
		{
			return (size_type(_impl._end_of_storage - _impl._data));
		}

		bool empty() const
		{
			return (size() == 0);
		}

		void reserve(size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			if (capacity() < n)
			{
				pointer newData (_impl.allocate(n));
				pointer newDataEnd (newData);
				int old_size (size());
				for (pointer p(_impl._data); p != _impl._end_data; ++p, ++newDataEnd)
				{
					::new (newDataEnd) value_type(*p);
					//_impl.construct(newDataEnd, *p);
					_impl.destroy(p);
				}
				_impl.deallocate(_impl._data, old_size);
				_impl._data = newData;
				_impl._end_data = newDataEnd;
				_impl._end_of_storage = _impl._data + n;
			}
		}

		reference operator[](size_type n)
		{
			return (_impl._data[n]);
		}

		const_reference operator[](size_type n) const
		{
			return (_impl._data[n]);
		}

		reference at(size_type n)
		{
			if (n >= size())
				throw std::out_of_range("vector::at");
			return (_impl._data[n]);
		}

		const_reference at(size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("vector::at");
			return (_impl._data[n]);
		}

		reference front()
		{
			return (*_impl._data);
		}

		const_reference front() const
		{
			return (*_impl._data);
		}

		reference back()
		{
			return (*(_impl._end_data - 1));
		}

		const_reference back() const
		{
			return (*(_impl._end_data - 1));
		}
		
		void destroy_data(void)
		{
			for (size_type i = 0; i < size(); ++i)
				_impl.destroy(_impl._data + i);
		}

		void reallocate_data(size_type n)
		{
			if (n > capacity())
			{
				pointer newData = _impl.allocate(n);
				_impl.deallocate(_impl._data, capacity());
				_impl._data = newData;
				_impl._end_of_storage = _impl._data + n;
			}
			_impl._end_data = _impl._data + n;
		}

		void assign(size_type n, const value_type &val)
		{
			destroy_data();
			reallocate_data(n);
			while (n--)
				_impl.construct(_impl._data + n, val);
		}

		template <class InputIterator>
		void assign(InputIterator first,
					typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
		{
			destroy_data();
			reallocate_data(ft::distance(first, last));
			pointer data = _impl._data;
			while (first != last)
			{
				::new (data) value_type(*first);
				first++;
				data++;
			}
		}

		void push_back(const value_type &val)
		{
			if (_impl._end_of_storage == _impl._end_data)
				reserve(std::max(capacity() * 2, size_type(1)));
			//new (_impl._end_data++) value_type(val);
			//_impl.construct(_impl._end_data++, val);
			*_impl._end_data++ = val;
		}

		void pop_back()
		{
			--_impl._end_data;
			_impl.destroy(_impl._end_data);
		}

		iterator insert(iterator position, const value_type &val)
		{
			difference_type offset = difference_type(position - begin());
			if (_impl._end_of_storage == _impl._end_data)
			{
				reserve(std::max(capacity() * 2, size_type(1)));
			}
			pointer last = _impl._end_data;
			_impl._end_data++;
			if (size() > 1)
			{
				pointer pos = _impl._data + offset;
				for (; last != pos; --last)
					*last = *(last - 1);
			}
			*last = val;
			return (iterator(last));
		}

		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n == 0)
				return;
			difference_type offset = difference_type(position - begin());
			size_type x (size() + n);
				
			if (x > capacity())
			{
				reserve(x);
			}
			_impl._end_data += n;
			pointer last = _impl._end_data - 1;
			pointer pos = _impl._data + offset + n - 1;
			for (; last != pos; --last)
				*last = *(last - n);
			while (n--)
				*last-- = val;
		}

		template <class InputIterator>
		void insert(iterator position, InputIterator first,
					typename enable_if<!is_integral<InputIterator>::value, InputIterator>::type last)
		{
			size_type n = ft::distance(first, last);
			if (n == 0)
				return;
			difference_type offset = difference_type(position - begin());
			if (size() + n > capacity())
			{
				reserve(std::max(std::max(capacity() * 2, size_type(1)), size() + n));
			}
			_impl._end_data += n;
			pointer lastp = _impl._end_data - 1;
			pointer pos = _impl._data + offset + n - 1;
			for (; lastp != pos; --lastp)
				*lastp = *(lastp - n);
			while (n--)
				_impl._data[offset++] = *first++;
		}

		iterator erase(iterator position)
		{
			if (position != end() - 1)
			{
				iterator first (position + 1);
				iterator last (end());
				iterator result (position);

				for (; first != last; ++result, ++first)
					*result = *first;
			}
			--_impl._end_data;
			_impl.destroy(_impl._end_data);
			return (position);
		}

		iterator erase(iterator first, iterator last)
		{
			if (first != last)
			{
				if (last != end())
				{
					iterator resultI = first;
					iterator firstI = last;
					iterator lastI = end();

					for (; firstI != lastI; ++resultI, ++firstI)
						*resultI = *firstI;
				}
				difference_type n = last - first;
				pointer pt = _impl._end_data - n;
				_impl._end_data -= n;
				while (n--)
					_impl.destroy(pt++);
			}
			return (first);
		}
		
		void swap(vector &x)
		{
			std::swap(_impl, x._impl);
		}

		void clear()
		{
			for (pointer pos = _impl._data; pos != _impl._end_data; ++pos)
				_impl.destroy(pos);

			_impl._end_data = _impl._data;
		}
		
		allocator_type
		get_allocator() const
		{
			return (allocator_type(_impl));
		}

	private:
		using Base::_impl;
	};

	template <typename T, typename Alloc>
	bool
	operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (lhs.size() == rhs.size() && ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template <typename T, typename Alloc>
	bool
	operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return !(lhs == rhs);
	}

	template <typename T, typename Alloc>
	bool
	operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(),
											rhs.begin(), rhs.end()));
	}

	template <typename T, typename Alloc>
	bool
	operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename T, typename Alloc>
	bool
	operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (rhs < lhs);
	}

	template <typename T, typename Alloc>
	bool
	operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <typename T, typename Alloc>
	void
	swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}
}

#endif