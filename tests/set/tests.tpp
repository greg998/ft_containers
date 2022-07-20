#ifndef TESTS_TPP
#define TESTS_TPP

# ifndef NS
#  define NS ft
# endif

#include "utility.tpp"
#include <set>
#include <iostream>

#if NS==ft
#include "set.tpp"
#endif

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
