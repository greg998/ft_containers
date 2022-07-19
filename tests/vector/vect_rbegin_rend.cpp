#include "tests.tpp"

int main()
{
    NS::vector<int> myvector(5); // 5 default-constructed ints
    displayVect(myvector);

    int i = 0;

    NS::vector<int>::reverse_iterator rit = myvector.rbegin();
    for (; rit != myvector.rend(); ++rit)
        *rit = ++i;

    displayVect(myvector);

    return 0;
}