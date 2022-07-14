#include "tests.hpp"

int main()
{
    NS::vector<int> myvector;

    for (int i = 0; i < 50; ++i)
        myvector.push_back(i);

    std::cout << "myvector stores " << int(myvector.size()) << " numbers.\n";

    return 0;
}