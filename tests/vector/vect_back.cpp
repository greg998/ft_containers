#include "tests.tpp"

int main()
{
    NS::vector<int> myvector;

    myvector.push_back(10);

    while (myvector.back() != 0)
    {
        myvector.push_back(myvector.back() - 1);
    }

    displayVect(myvector);

    return 0;
}