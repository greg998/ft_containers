#include "tests.tpp"

int main()
{
    NS::vector<int> myvector;
    for (int i = 1; i <= 5; i++)
        myvector.push_back(i);

    displayVect(myvector);

    return 0;
}