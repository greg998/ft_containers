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
            : current (Iterator())
        {

        }
        explicit random_access_iterator(const Iterator &src)
            : current(src)
        {
            
        }

        template<typename _Iter>
        random_access_iterator(const random_access_iterator<_Iter,
			  typename __gnu_cxx::__enable_if<
      	       (std::__are_same<_Iter, typename Container::pointer>::__value),
		      Container>::__type >& __i)
        : current(__i.base()) { }

        const Iterator &base(void) const
        {
            return (current);
        }

        random_access_iterator &operator=(const random_access_iterator &rhs)
        {
            current = rhs.current;
            return (*this);
        }

        bool    operator==(const random_access_iterator &rhs)
        {
            return (current == rhs.current);
        }

        bool    operator!=(const random_access_iterator &rhs)
        {
            return (current != rhs.current);
        }

        reference  operator*(void) const
        {
            return (*current);
        }
        pointer  operator->(void) const
        {
            return (current);
        }

        random_access_iterator  &operator++(void)
        {
            ++current;
            return (*this);
        }

        random_access_iterator  operator++(int)
        {
            return (random_access_iterator(current++));
        }

        random_access_iterator  &operator--(void)
        {
            --current;
            return (*this);
        }

        random_access_iterator  operator--(int)
        {
            return (random_access_iterator(current--));
        }

    };
}
#endif