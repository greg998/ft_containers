#include "tests.hpp"

int main()
{                                                         // constructors used in the same order as described above:
    NS::vector<int> first;                               // empty vector of ints
    NS::vector<int> second(4, 100);                      // four ints with value 100
    NS::vector<int> third(second.begin(), second.end()); // iterating through second
    NS::vector<int> fourth(third);                       // a copy of third

    // the iterator constructor can also be used to construct from arrays:
    int myints[] = {16, 2, 77, 29};
    NS::vector<int> fifth(myints, myints + sizeof(myints) / sizeof(int));

    std::cout << "The contents of fifth are:";
    for (NS::vector<int>::iterator it = fifth.begin(); it != fifth.end(); ++it)
        std::cout << ' ' << *it;
    std::cout << '\n';
    return (0);
}