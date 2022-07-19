#include "tests.tpp"

int main()
{
    NS::vector<int> foo(3, 0);
    NS::vector<int> bar(5, 0);
    displayVect(foo);
    displayVect(bar);

    bar = foo;
    foo = NS::vector<int>();

    displayVect(foo);
    displayVect(bar);
    return 0;
}