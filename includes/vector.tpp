#ifndef VECTOR_TPP
#define VECTOR_TPP
#include <iostream>
#include "random_access_iterator.tpp"

namespace ft
{
	template <typename _Tp1>
	struct rebind
	{
		typedef std::allocator<_Tp1> other;
	};
	template <class T, typename Alloc>
	class vector_base
	{
	public:
		typedef Alloc allocator_type;
		typedef typename __gnu_cxx::__alloc_traits<Alloc>::template rebind<T>::other _Tp_alloc_type;
		typedef typename __gnu_cxx::__alloc_traits<_Tp_alloc_type>::pointer
			pointer;
		vector_base(){};
		vector_base(const allocator_type &__a)
			: _impl(__a){};

	protected:
		class vector_impl : public _Tp_alloc_type
		{
		public:
			pointer _data;
			pointer _end_data;
			pointer _end_of_storage;
			vector_impl() _GLIBCXX_NOEXCEPT_IF(
				std::is_nothrow_default_constructible<_Tp_alloc_type>::value)
				: _Tp_alloc_type()
			{
			}
			vector_impl(_Tp_alloc_type const &__a) _GLIBCXX_NOEXCEPT
				: _Tp_alloc_type(__a)
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
		typedef Alloc allocator_type;
		typedef typename vector_base<T, Alloc>::_Tp_alloc_type _Tp_alloc_type;
		typedef __gnu_cxx::__alloc_traits<_Tp_alloc_type> _Alloc_traits;
		typedef typename _Alloc_traits::reference reference;
		typedef typename _Alloc_traits::const_reference const_reference;
		typedef typename Base::pointer pointer;
		typedef typename _Alloc_traits::const_pointer const_pointer;
		typedef random_access_iterator<pointer, vector> iterator;
      	typedef random_access_iterator<const_pointer, vector> const_iterator;

		explicit vector(const allocator_type &alloc = allocator_type())
			: Base(alloc)
		{
		}
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: Base(alloc)
		{
			std::cout << "constructor 2\n";
			_impl._data = _M_get_Tp_allocator().allocate(n);
			_impl._end_data = _impl._data;
			while (n--)
				_Alloc_traits::construct(_M_get_Tp_allocator(), _impl._end_data++, val);
			_impl._end_of_storage = _impl._end_data;
		}
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last,
		// 	   const allocator_type &alloc = allocator_type())
		// {
		// 	std::cout << "constructor 3\n";

		// }
		void copyData(const vector &x)
		{
		}
		vector(const vector &x)
			: Base()
		{
			std::cout << "copy constructor\n";
		}
		~vector()
		{
			get_allocator().deallocate(_impl._data, capacity());
		}
		vector &operator=(const vector &x);
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
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;
		size_type size() const
		{
			return (size_type(this->_data_end - this->_impl._data));
		}
		size_type max_size() const
		{
			return (get_allocator().max_size());
		}
		void resize(size_type n, value_type val = value_type())
		{
			size_type size = this->size();
			if (n < size)
			{
				while (size-- != n)
				{
					get_allocator().destroy(_impl._data + size);
				}
			}
			else if (n > size)
			{
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
				pointer newData = get_allocator().allocate(n);
				int old_size = size();
				while (old_size--)
					get_allocator().construct(newData + old_size, _impl._data[old_size]);
				get_allocator().deallocate(_impl._data, _impl._end_of_storage);
				_impl._data = newData;
				_impl._end_data = newData + old_size;
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
			return (this->at(n));
		}
		// reference front()
		// {
		// 	return (*begin());
		// }
		// const_reference front() const
		// {
		// 	return (*begin());
		// }
		// reference back()
		// {
		// 	return (*(end() - 1));
		// }
		// const_reference back() const
		// {
		// 	return (*(end() - 1));
		// }
		template <class InputIterator>
		void assign(InputIterator first, InputIterator last);
		void assign(size_type n, const value_type &val);
		void push_back(const value_type &val);
		void pop_back();
		// iterator insert (iterator position, const value_type& val);
		// void insert (iterator position, size_type n, const value_type& val);
		// template <class InputIterator>
		// void insert (iterator position, InputIterator first, InputIterator last);
		// iterator erase (iterator position);
		// iterator erase (iterator first, iterator last);
		void swap(vector &x);
		void clear()
		{
			if (size_type _n = _impl._end_data - _impl._data)
			{
				for (pointer pos = _impl._data; pos != _impl._end_data; ++pos)
					get_allocator().destroy(*pos);

				_impl._end_data = _impl._data;
			}
		}
		_Tp_alloc_type &
		_M_get_Tp_allocator() _GLIBCXX_NOEXCEPT
		{
			return this->_impl;
		}

		const _Tp_alloc_type &
		_M_get_Tp_allocator() const _GLIBCXX_NOEXCEPT
		{
			return this->_impl;
		}

		allocator_type
		get_allocator() const _GLIBCXX_NOEXCEPT
		{
			return allocator_type(_M_get_Tp_allocator());
		}

	private:
		using Base::_impl;
	};
}

#endif