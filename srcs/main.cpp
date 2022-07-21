#include <iostream>
#include <string>

#include <stdlib.h>
#include "vector.tpp"
#include "stack.tpp"
#include <vector>
#include <cstdlib>
#include <new>
#include <limits>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <list>
#include <deque>
#include <stack>
#include <map>
#include "map.tpp"
#include <set>

#define ft std

namespace mmap_allocator_namespace
{
  // See StackOverflow replies to this answer for important commentary about inheriting from std::allocator before replicating this code.
  template <typename T>
  class mmap_allocator : public std::allocator<T>
  {
  public:
    typedef size_t size_type;
    typedef T *pointer;
    typedef const T *const_pointer;

    template <typename _Tp1>
    struct rebind
    {
      typedef mmap_allocator<_Tp1> other;
    };

    pointer allocate(size_type n, const void *hint = 0)
    {
      fprintf(stderr, "Alloc %d bytes.\n", n * sizeof(T));
      return std::allocator<T>::allocate(n, hint);
    }

    void deallocate(pointer p, size_type n)
    {
      fprintf(stderr, "Dealloc %d bytes (%p).\n", n * sizeof(T), p);
      return std::allocator<T>::deallocate(p, n);
    }

    mmap_allocator() throw() : std::allocator<T>() { fprintf(stderr, "Hello allocator!\n"); }
    mmap_allocator(const mmap_allocator &a) throw() : std::allocator<T>(a) {}
    template <class U>
    mmap_allocator(const mmap_allocator<U> &a) throw() : std::allocator<T>(a) {}
    ~mmap_allocator() throw() {}
  };
}

template <typename T>
void display_vector_info(const ft::vector<T> &vect)
{
  std::cout << "size " << vect.size() << std::endl;
  std::cout << "max_size " << vect.max_size() << std::endl;
  std::cout << "capacity " << vect.capacity() << std::endl;
  std::cout << "empty " << vect.empty() << std::endl;
}

class A
{
private:
  int x;

public:
  A() {}
  A(int x)
  {
    std::cout << "A " << x << std::endl;
    this->x = x;
  }
  A(const A &src) : x(src.x) { std::cout << "copy A " << x << std::endl; }
  const A &operator=(const A &rhs)
  {
    // std::cout << "A assignment" << std::endl;
    x = rhs.x;
    return *this;
  }
  ~A()
  {
    std::cout << "A destructor " << x << std::endl;
  }
  friend std::ostream &operator<<(std::ostream &o, const A &rhs)
  {
    o << rhs.x;
    return o;
  }
};

int main()
{
  // ft::vector<A> first;                               // empty vector of ints
  // std::cout << "-----------------\n";
  // ft::vector<A> second (4,100);                       // four ints with value 100
  // std::cout << "-----------------\n";
  // ft::vector<A> third (second.begin(),second.end());  // iterating through second
  // std::cout << "-----------------\n";
  // ft::vector<A> fourth (third);                       // a copy of third
  // // // the iterator constructor can also be used to construct from arrays:
  // int myints[] = {16,2,77,29};

  // ft::vector<A> fifth (myints, myints + sizeof(myints) / sizeof(int) );

  // std::cout << "The contents of fifth are:";
  // for (ft::vector<A>::iterator it = fifth.begin(); it != fifth.end(); ++it)
  //   std::cout << ' ' << *it;
  // // A a(2);
  // // //a = *myints;

  // // new (&a) A(*myints);
  // std::cout << '\n';
  // fifth.reserve(10);

  ft::map<char, int> ve;
  ft::map<char, int>::const_iterator itx (ve.begin());
  ft::map<char, int>::const_iterator te(itx);
  std::allocator
  return 0;
}