#include "tests.tpp"

int main()
{
    NS::vector<int> foo(3, 100); // three ints with a value of 100
    NS::vector<int> bar(5, 200); // five ints with a value of 200
    displayVect(foo);
    displayVect(bar);

    foo.swap(bar);

    displayVect(foo);
    displayVect(bar);

    NS::swap(foo, bar);

    displayVect(foo);
    displayVect(bar);

    return 0;
}