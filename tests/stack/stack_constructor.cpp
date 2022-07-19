#include "tests.tpp"

int main ()
{
  std::deque<int> mydeque (3,100);          // deque with 3 elements
  std::vector<int> myvector (2,200);        // vector with 2 elements

  NS::stack<int> first;                    // empty stack
  NS::stack<int, std::deque<int> > second (mydeque);         // stack initialized to copy of deque

  NS::stack<int,std::vector<int> > third;  // empty stack using vector
  NS::stack<int,std::vector<int> > fourth (myvector);

  std::cout << "size of first: " << first.size() << '\n';
  std::cout << "size of second: " << second.size() << '\n';
  std::cout << "size of third: " << third.size() << '\n';
  std::cout << "size of fourth: " << fourth.size() << '\n';

  NS::stack<int,std::vector<int> > fifth = fourth;

  displayStack(fourth);
  displayStack(fifth);
  return 0;
}