#ifndef ITERATOR_TPP
#define ITERATOR_TPP
#include <iostream>
#include "iterator_traits.tpp"
#include "iterator.tpp"

namespace ft
{
	template <class Category, class T, class Distance = ptrdiff_t,
			  class Pointer = T *, class Reference = T &>
	class iterator
	{
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
		typedef Category iterator_category;
	};

	template <class Iterator>
	class reverse_iterator : public iterator<typename iterator_traits<Iterator>::iterator_category,
											 typename iterator_traits<Iterator>::value_type,
											 typename iterator_traits<Iterator>::difference_type,
											 typename iterator_traits<Iterator>::pointer,
											 typename iterator_traits<Iterator>::reference>
	{
	protected:
		Iterator current;
		typedef iterator_traits<Iterator> _traits_type;

	public:
		typedef Iterator iterator_type;
		typedef typename _traits_type::reference reference;
		typedef typename _traits_type::difference_type difference_type;
		typedef typename _traits_type::pointer pointer;

		reverse_iterator()
			: current()
		{
		}

		explicit reverse_iterator(iterator_type it)
			: current(it)
		{
		}

		reverse_iterator(const reverse_iterator &__x)
			: current(__x.current) {}
		template <class Iter>
		reverse_iterator(const reverse_iterator<Iter> &rev_it)
			: current(rev_it.base())
		{
		}

		iterator_type base() const
		{
			return (current);
		}

		reference operator*(void) const
		{
			Iterator tmp = current;
			return (*--tmp);
		}

		reverse_iterator operator+(difference_type rhs) const
		{
			return (reverse_iterator(current - rhs));
		}

		reverse_iterator &operator++(void)
		{
			--current;
			return (*this);
		}

		reverse_iterator operator++(int)
		{
			return (reverse_iterator(current--));
		}

		reverse_iterator &operator+=(difference_type rhs)
		{
			current -= rhs;
			return (*this);
		}

		reverse_iterator operator-(difference_type rhs) const
		{
			return (reverse_iterator(current + rhs));
		}

		reverse_iterator &operator--(void)
		{
			++current;
			return (*this);
		}

		reverse_iterator operator--(int)
		{
			return (reverse_iterator(current++));
		}

		reverse_iterator &operator-=(difference_type rhs)
		{
			current += rhs;
			return (*this);
		}

		pointer operator->(void) const
		{
			return &(operator*());
		}

		reference operator[](difference_type rhs) const
		{
			return *(*this + rhs);
		}
	};

	template <class Iterator>
	inline bool operator==(const reverse_iterator<Iterator> &lhs,
						   const reverse_iterator<Iterator> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename IteratorL, typename IteratorR>
	inline bool operator==(const reverse_iterator<IteratorL> &lhs,
						   const reverse_iterator<IteratorR> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <class Iterator>
	inline bool operator!=(const reverse_iterator<Iterator> &lhs,
						   const reverse_iterator<Iterator> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <typename IteratorL, typename IteratorR>
	inline bool operator!=(const reverse_iterator<IteratorL> &lhs,
						   const reverse_iterator<IteratorR> &rhs)
	{
		return (!(lhs == rhs));
	}

	template <class Iterator>
	inline bool operator<(const reverse_iterator<Iterator> &lhs,
						  const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() < lhs.base());
	}

	template <typename IteratorL, typename IteratorR>
	inline bool operator<(const reverse_iterator<IteratorL> &lhs,
						  const reverse_iterator<IteratorR> &rhs)
	{
		return (rhs.base() < lhs.base());
	}

	template <class Iterator>
	inline bool operator<=(const reverse_iterator<Iterator> &lhs,
						   const reverse_iterator<Iterator> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <typename IteratorL, typename IteratorR>
	inline bool operator<=(const reverse_iterator<IteratorL> &lhs,
						   const reverse_iterator<IteratorR> &rhs)
	{
		return (!(rhs < lhs));
	}

	template <class Iterator>
	inline bool operator>(const reverse_iterator<Iterator> &lhs,
						  const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() > lhs.base());
	}

	template <typename IteratorL, typename IteratorR>
	inline bool operator>(const reverse_iterator<IteratorL> &lhs,
						  const reverse_iterator<IteratorR> &rhs)
	{
		return (rhs.base() > lhs.base());
	}

	template <class Iterator>
	inline bool operator>=(const reverse_iterator<Iterator> &lhs,
						   const reverse_iterator<Iterator> &rhs)
	{
		return (!(lhs < rhs));
	}
	
	template <typename IteratorL, typename IteratorR>
	inline bool operator>=(const reverse_iterator<IteratorL> &lhs,
						   const reverse_iterator<IteratorR> &rhs)
	{
		return (!(lhs < rhs));
	}

	template <class Iterator>
	inline reverse_iterator<Iterator> operator+(
		typename reverse_iterator<Iterator>::difference_type n,
		const reverse_iterator<Iterator> &rev_it)
	{
		return (reverse_iterator<Iterator>(rev_it.base() - n));
	}

	template <class Iterator>
	inline typename reverse_iterator<Iterator>::difference_type operator-(
		const reverse_iterator<Iterator> &lhs,
		const reverse_iterator<Iterator> &rhs)
	{
		return (rhs.base() - lhs.base());
	}

	template <typename IteratorL, typename IteratorR>
	inline typename reverse_iterator<IteratorL>::difference_type
	operator-(const reverse_iterator<IteratorL> &lhs,
			  const reverse_iterator<IteratorR> &rhs)
	{
		return (rhs.base() - lhs.base());
	}

	// only random access iterator overload '-'
	template <typename RandomAccessIterator>
	inline typename iterator_traits<RandomAccessIterator>::difference_type
	_distance(RandomAccessIterator first, RandomAccessIterator last,
			  std::random_access_iterator_tag)
	{
		return (last - first);
	}

	template <typename InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
	_distance(InputIterator first, InputIterator last,
			  std::input_iterator_tag)
	{
		typename iterator_traits<InputIterator>::difference_type n = 0;
		while (first++ != last)
			++n;
		return (n);
	}
	
	template <class InputIterator>
	typename iterator_traits<InputIterator>::difference_type
	distance(InputIterator first, InputIterator last)
	{
		return (_distance(first, last,
						  typename iterator_traits<InputIterator>::iterator_category()));
	}
}

#endif