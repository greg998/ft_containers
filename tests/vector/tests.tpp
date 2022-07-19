#ifndef TESTS_HPP
#define TESTS_HPP

#ifndef NS
#define NS FT
#endif

#include "vector.tpp"
#include <vector>

template <class T,
          class Alloc>
void displayVect(const NS::vector<T, Alloc> &c)
{
    std::cout << "----------------\n";
    std::cout << "max_size " << c.max_size() << "\n";
    std::cout << "capacity " << c.capacity() << "\n";
    std::cout << "size " << c.size() << "\n";
    for (typename NS::vector<T, Alloc>::const_iterator it = c.begin(); it != c.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << "\n";
}
#endif