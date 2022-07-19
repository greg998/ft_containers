#include "tests.tpp"

int main()
{
    NS::vector<int> myvector(10); // 10 zero-initialized ints
    displayVect(myvector);

    // assign some values:
    for (unsigned i = 0; i < myvector.size(); i++)
        myvector.at(i) = i;

    displayVect(myvector);


    return 0;
}