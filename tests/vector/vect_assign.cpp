#include "tests.tpp"

int main()
{
    NS::vector<int> first;
    NS::vector<int> second;
    NS::vector<int> third;

    first.assign(7, 100); // 7 ints with a value of 100

    NS::vector<int>::iterator it;
    it = first.begin() + 1;

    second.assign(it, first.end() - 1); // the 5 central values of first

    int myints[] = {1776, 7, 4};
    third.assign(myints, myints + 3); // assigning from array.

    displayVect(first);
    displayVect(second);
    displayVect(third);
    return 0;
}