#ifndef VECTOR_TPP
#define VECTOR_TPP
#include <iostream>

namespace ft
{
	template <class T, class Alloc = std::allocator<T> >
	class vector
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
			: _Tp_alloc_type(alloc), _size(0), _capacity(0), _data(NULL)
		{
		}
		explicit vector(size_type n, const value_type &val = value_type(),
						const allocator_type &alloc = allocator_type())
			: _Tp_alloc_type(alloc), _size(n), _capacity(n)
		{
			std::cout << "constructor 2\n";
			_data = _Tp_alloc_type.allocate(_size);
			while (n--)
			{
				_Tp_alloc_type.construct(_data + n, val);
			}
		}
		// template <class InputIterator>
		// vector(InputIterator first, InputIterator last,
		// 	   const allocator_type &alloc = allocator_type())
		// {
		// 	std::cout << "constructor 3\n";

		// }
		vector(const vector &x)
			: _Tp_alloc_type(x._Tp_alloc_type), _size (x._size), _capacity (x._capacity)
		{
			std::cout << "copy constructor\n";

		}
		~vector()
		{
			_Tp_alloc_type.deallocate(_data, _capacity);
		}
		vector& operator= (const vector& x);
		//iterator begin();
		//const_iterator begin() const;
		//iterator end();
		//const_iterator end() const;
		//reverse_iterator rbegin();
		//const_reverse_iterator rbegin() const;
		//reverse_iterator rend();
		//const_reverse_iterator rend() const;
		size_type size() const
		{
			return (_size);
		}
		size_type max_size() const
		{
			return (_Tp_alloc_type.max_size());
		}
		void resize (size_type n, value_type val = value_type())
		{
			if (n < _size)
			{
				while (_size-- != n)
				{
					_Tp_alloc_type.destroy(_data + _size);
				}
			}
			else if (n > _size)
			{

			}
		}
		size_type capacity() const
		{
			return (_capacity);
		}
		bool empty() const
		{
			return (_size == 0);
		}
		void reserve (size_type n)
		{
			if (n > this->max_size())
				throw std::length_error("vector::reserve");
			if (n > _size)
			{
				pointer newData = _Tp_alloc_type.allocate(n);
				int	size(_size);
				while (size--)
					_Tp_alloc_type.construct(newData + _size, _data[size]);
				_Tp_alloc_type.deallocate(_data, _capacity);
				_capacity = n;
			}
		}

		reference operator[] (size_type n)
		{
			return (_data[n]);
		}

		const_reference operator[] (size_type n) const
		{
			return (_data[n]);
		}
		reference at (size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("vector::at");
			return (_data[n]);
		}
		const_reference at (size_type n) const
		{
			return (this->at(n));
		}
		reference front()
		{
			return (_data[0]);
		}
		const_reference front() const
		{
			return (this->front());
		}
		reference back()
		{
			return (_data[_size - 1]);
		}
		const_reference back() const
		{
			return (this->back());
		}
		template <class InputIterator>
  		void assign (InputIterator first, InputIterator last);
		void assign (size_type n, const value_type& val);
		void push_back (const value_type& val);
		void pop_back();
		//iterator insert (iterator position, const value_type& val);
		//void insert (iterator position, size_type n, const value_type& val);
		template <class InputIterator>
    	//void insert (iterator position, InputIterator first, InputIterator last);
		//iterator erase (iterator position);
		//iterator erase (iterator first, iterator last);
		void swap (vector& x);
		void clear()
		{
			while (_size--)
			{
				_Tp_alloc_type.destroy(_data + _size);
			}
		}
		allocator_type get_allocator() const
		{
			return (_Tp_alloc_type);
		}

	private:
		allocator_type _Tp_alloc_type;
		size_type	_size;
		size_type	_capacity;
		pointer		_data;

	};
}

#endif