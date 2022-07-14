#include "tests.hpp"

int main ()
{
  NS::vector<int> foo (3,0);
  NS::vector<int> bar (5,0);

  bar = foo;
  foo = NS::vector<int>();

  std::cout << "Size of foo: " << int(foo.size()) << '\n';
  std::cout << "Size of bar: " << int(bar.size()) << '\n';
  return 0;
}