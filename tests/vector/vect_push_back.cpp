#include "tests.tpp"

int main()
{
    NS::vector<int> myvector;

    for (int i = 0; i < 50; ++i)
        myvector.push_back(i);

    displayVect(myvector);
    std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

    return 0;
}