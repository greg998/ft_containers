#ifndef VECTOR_TPP
#define VECTOR_TPP
#include <iostream>

namespace ft
{
	template <class T, class Alloc>
	class vector_base
	{
	public:
		typedef Alloc allocator_type;
		typedef typename allocator_type::pointer pointer;
	protected:
		pointer _data;
		pointer _end_data;
		pointer _end_of_storage;

	};
	template <class T, class Alloc = std::allocator<T> >
	class vector: public vector_base<T, Alloc>
	{
	public:
		typedef T value_type;
		typedef size_t size_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

		explicit vector(const allocator_type &alloc = allocator_type())
			: _Tp_alloc_type(alloc), _data(NULL), _end_data(NULL), _end_of_storage(NULL)
		{
		}
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: _Tp_alloc_type(alloc)
		{
			std::cout << "constructor 2\n";
			_data = _Tp_alloc_type.allocate(n);
			_end_data = _data;
			while (n--)
				_Tp_alloc_type.construct(_end_data++, val);
		}
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last,
		// 	   const allocator_type &alloc = allocator_type())
		// {
		// 	std::cout << "constructor 3\n";

		// }
		void	copyData(const vector &x)
		{

		}
		vector(const vector &x)
			: _Tp_alloc_type(x._Tp_alloc_type), _data(NULL), _end_data(NULL), _end_of_storage(NULL)
		{
			std::cout << "copy constructor\n";
		}
		~vector()
		{
			_Tp_alloc_type.deallocate(_data, capacity());
		}
		vector &operator=(const vector &x);
		// iterator begin();
		// const_iterator begin() const;
		// iterator end();
		// const_iterator end() const;
		// reverse_iterator rbegin();
		// const_reverse_iterator rbegin() const;
		// reverse_iterator rend();
		// const_reverse_iterator rend() const;
		size_type size() const
		{
			return (size_type(this->_data_end - this->_data));
		}
		size_type max_size() const
		{
			return (_Tp_alloc_type.max_size());
		}
		void resize(size_type n, value_type val = value_type())
		{
			size_type size = this->size();
			if (n < size)
			{
				while (size-- != n)
				{
					_Tp_alloc_type.destroy(_data + size);
				}
			}
			else if (n > size)
			{
			}
		}
		size_type capacity() const
		{
			return (size_type(_end_of_storage - _data));
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
				pointer newData = _Tp_alloc_type.allocate(n);
				int old_size = size();
				while (old_size--)
					_Tp_alloc_type.construct(newData + old_size, _data[old_size]);
				_Tp_alloc_type.deallocate(_data, _end_of_storage);
				_data = newData;
				_end_data = newData + old_size;
				_end_of_storage = _data + n;
			}
		}

		reference operator[](size_type n)
		{
			return (_data[n]);
		}

		const_reference operator[](size_type n) const
		{
			return (_data[n]);
		}
		reference at(size_type n)
		{
			if (n >= size())
				throw std::out_of_range("vector::at");
			return (_data[n]);
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
		template <class InputIterator>
		// void insert (iterator position, InputIterator first, InputIterator last);
		// iterator erase (iterator position);
		// iterator erase (iterator first, iterator last);
		void swap(vector &x);
		void clear()
		{
			if (size_type _n = _end_data - _data)
			{
				for (pointer pos = _data; pos != _end_data; ++pos)
					_Tp_alloc_type.destroy(*pos);

				_end_data = _data;
			}
		}
		allocator_type get_allocator() const
		{
			return (_Tp_alloc_type);
		}

	private:
		pointer _data;
		pointer _end_data;
		pointer _end_of_storage;
	};
}

#endif