#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR
#include "iterator_traits.tpp"
#include "iterator_tags.hpp"
namespace ft
{
	
	template <typename Iterator, typename Container>
	class random_access_iterator
	{
	protected:
		Iterator current;
		typedef iterator_traits<Iterator> _traits_type;

	public:
		typedef Iterator iterator_type;
		typedef typename _traits_type::iterator_category iterator_category;
		typedef typename _traits_type::value_type value_type;
		typedef typename _traits_type::difference_type difference_type;
		typedef typename _traits_type::reference reference;
		typedef typename _traits_type::pointer pointer;

		random_access_iterator()
			: current(Iterator())
		{
		}
		explicit random_access_iterator(const Iterator &src)
			: current(src)
		{
		}

		template <typename _Iter>
		random_access_iterator(const random_access_iterator<_Iter,
															typename __gnu_cxx::__enable_if<
																(std::__are_same<_Iter, typename Container::pointer>::__value),
																Container>::__type> &__i)
			: current(__i.base()) {}

		const Iterator &base(void) const
		{
			return (current);
		}

		random_access_iterator &operator=(const random_access_iterator &rhs)
		{
			current = rhs.current;
			return (*this);
		}

		// bool operator!=(const random_access_iterator &rhs)
		// {
		// 	return (current != rhs.current);
		// }

		reference operator*(void) const
		{
			return (*current);
		}

		pointer operator->(void) const
		{
			return (current);
		}

		random_access_iterator &operator++(void)
		{
			++current;
			return (*this);
		}

		random_access_iterator operator++(int)
		{
			return (random_access_iterator(current++));
		}

		random_access_iterator &operator--(void)
		{
			--current;
			return (*this);
		}

		random_access_iterator operator--(int)
		{
			return (random_access_iterator(current--));
		}

		random_access_iterator operator+(difference_type rhs) const
		{
			return (random_access_iterator(current + rhs));
		}

		random_access_iterator operator-(difference_type rhs) const
		{
			return (random_access_iterator(current - rhs));
		}

		random_access_iterator &operator+=(difference_type rhs)
		{
			current += rhs;
			return (*this);
		}

		random_access_iterator &operator-=(difference_type rhs)
		{
			current -= rhs;
			return (*this);
		}

		reference operator[](difference_type rhs) const
		{
			return *(*this + rhs);
		}
	};
	// allow difference_type x = it - it but it + it forbidden
	template <typename IteratorL, typename IteratorR, typename Container>
	inline typename random_access_iterator<IteratorL, Container>::difference_type
	operator-(const random_access_iterator<IteratorL, Container> &lhs,
			  const random_access_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() - rhs.base());
	}
	template <typename Iterator, typename Container>
	inline typename random_access_iterator<Iterator, Container>::difference_type
	operator-(const random_access_iterator<Iterator, Container> &lhs,
			  const random_access_iterator<Iterator, Container> &rhs)
	{
		return (lhs.base() - rhs.base());
	}

	template <typename Iterator, typename Container>
	inline random_access_iterator<Iterator, Container>
	operator+(typename random_access_iterator<Iterator, Container>::difference_type lhs,
			  const random_access_iterator<Iterator, Container> &rhs)
	{
		return (random_access_iterator<Iterator, Container>(rhs.base() + lhs));
	}
	//---------------
	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator==(const random_access_iterator<IteratorL, Container> &lhs,
			   const random_access_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename _Iterator, typename Container>
	inline bool
	operator==(const random_access_iterator<_Iterator, Container> &lhs,
			   const random_access_iterator<_Iterator, Container> &rhs)
	{
		return (lhs.base() == rhs.base());
	}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator!=(const random_access_iterator<IteratorL, Container> &lhs,
			   const random_access_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	template <typename _Iterator, typename Container>
	inline bool
	operator!=(const random_access_iterator<_Iterator, Container> &lhs,
			   const random_access_iterator<_Iterator, Container> &rhs)
	{
		return (lhs.base() != rhs.base());
	}

	// Random access iterator requirements
	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator<(const random_access_iterator<IteratorL, Container> &lhs,
			  const random_access_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename _Iterator, typename Container>
	inline bool
	operator<(const random_access_iterator<_Iterator, Container> &lhs,
			  const random_access_iterator<_Iterator, Container> &rhs)
	{
		return (lhs.base() < rhs.base());
	}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator>(const random_access_iterator<IteratorL, Container> &lhs,
			  const random_access_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename _Iterator, typename Container>
	inline bool
	operator>(const random_access_iterator<_Iterator, Container> &lhs,
			  const random_access_iterator<_Iterator, Container> &rhs)
	{
		return (lhs.base() > rhs.base());
	}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator<=(const random_access_iterator<IteratorL, Container> &lhs,
			   const random_access_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename _Iterator, typename Container>
	inline bool
	operator<=(const random_access_iterator<_Iterator, Container> &lhs,
			   const random_access_iterator<_Iterator, Container> &rhs)
	{
		return (lhs.base() <= rhs.base());
	}

	template <typename IteratorL, typename IteratorR, typename Container>
	inline bool
	operator>=(const random_access_iterator<IteratorL, Container> &lhs,
			   const random_access_iterator<IteratorR, Container> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}

	template <typename _Iterator, typename Container>
	inline bool
	operator>=(const random_access_iterator<_Iterator, Container> &lhs,
			   const random_access_iterator<_Iterator, Container> &rhs)
	{
		return (lhs.base() >= rhs.base());
	}
}
#endif