#include "tests.tpp"

int main()
{
    NS::vector<int> myvector;

    // set some initial content:
    for (int i = 1; i < 10; i++)
        myvector.push_back(i);
    displayVect(myvector);

    myvector.resize(5);
    displayVect(myvector);
    myvector.resize(8, 100);
    displayVect(myvector);
    myvector.resize(12);
    displayVect(myvector);
    
    return 0;
}