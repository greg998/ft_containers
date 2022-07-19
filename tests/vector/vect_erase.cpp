#include "tests.tpp"

int main()
{
    NS::vector<int> myvector;

    // set some values (from 1 to 10)
    for (int i = 1; i <= 10; i++)
        myvector.push_back(i);
    displayVect(myvector);

    // erase the 6th element
    myvector.erase(myvector.begin() + 5);
    displayVect(myvector);

    // erase the first 3 elements:
    myvector.erase(myvector.begin(), myvector.begin() + 3);
    displayVect(myvector);

    return 0;
}