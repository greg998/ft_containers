#include "tests.tpp"

int main()
{
    NS::vector<int> myvector;

    // set some content in the vector:
    for (int i = 0; i < 100; i++)
        myvector.push_back(i);

    displayVect(myvector);
    return 0;
}