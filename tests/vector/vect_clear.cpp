#include "tests.tpp"

int main()
{
    NS::vector<int> myvector;
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);

    displayVect(myvector);

    myvector.clear();
    myvector.push_back(1101);
    myvector.push_back(2202);

    displayVect(myvector);

    return 0;
}