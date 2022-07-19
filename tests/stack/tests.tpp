#ifndef TESTS_TPP
#define TESTS_TPP

# ifndef NS
#  define NS FT
# endif

#include "stack.tpp"
#include <stack>
#include <vector>
#include <deque>

template <class T,
          class Container>
void displayStack(NS::stack<T, Container> &c)
{
    std::cout << "----------------\n";
    std::cout << "size " << c.size() << "\n";
    while (!c.empty())
    {
        std::cout << c.top() << " ";
        c.pop();
    }
    std::cout << "\n";
}
#endif
