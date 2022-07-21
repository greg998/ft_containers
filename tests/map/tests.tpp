#ifndef TESTS_TPP
#define TESTS_TPP

#ifndef NS
#define NS FT
#endif

#include <iostream>

#ifndef STD
#include "map.tpp"
#else
#include <map>
#endif

template <class Key,     // map::key_type
          class T,       // map::mapped_type
          class Compare, // map::key_compare
          class Alloc>   // map::allocator_type
void displayMap(const NS::map<Key, T, Compare, Alloc> &m)
{
    typedef NS::map<Key, T, Compare, Alloc> map_type;
    std::cout << "---------------\n";
    std::cout << "max_size: " << m.max_size() << "\n";
    std::cout << "size: " << m.size() << "\n";
    for (typename map_type::const_iterator it = m.begin(); it != m.end(); ++it)
    {
        std::cout << it->first << " => " << it->second << "\n";
    }
}
#endif
