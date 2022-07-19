#include "tests.tpp"

int main()
{
    NS::vector<int> myvector;
    int sum(0);
    myvector.push_back(100);
    myvector.push_back(200);
    myvector.push_back(300);
    displayVect(myvector);
    while (!myvector.empty())
    {
        sum += myvector.back();
        myvector.pop_back();
    }

    displayVect(myvector);
    std::cout << "The elements of myvector add up to " << sum << '\n';

    return 0;
}