#ifndef TESTS_TPP
#define TESTS_TPP

# ifndef NS
#  define NS FT
# endif

#include "set.tpp"
#include "utility.tpp"
#include <set>



template < class T,
           class Compare,
           class Alloc
           >
void	displaySet(const NS::set<T, Compare, Alloc> &c)
{
	std::cout << "----------------\n";
	std::cout << "max_size " << c.max_size() << "\n";
	std::cout << "size " << c.size() << "\n";
	for (typename NS::set<T, Compare, Alloc>::iterator it = c.begin(); it != c.end(); ++it)
	{
		std::cout << *it << " ";
	}
	std::cout << "\n";
}

#endif
