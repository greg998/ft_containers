#include "tests.tpp"

int main()
{
    NS::vector<int> myvector;

    myvector.push_back(78);
    myvector.push_back(16);
    displayVect(myvector);

    // now front equals 78, and back 16

    myvector.front() -= myvector.back();

    std::cout << "myvector.front() is now " << myvector.front() << '\n';

    return 0;
}