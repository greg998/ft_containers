#include "tests.tpp"

int main()
{
    NS::vector<int> myvector(10); // 10 zero-initialized elements
    displayVect(myvector);

    NS::vector<int>::size_type sz = myvector.size();

    // assign some values:
    for (unsigned i = 0; i < sz; i++)
        myvector[i] = i;
    displayVect(myvector);

    // reverse vector using operator[]:
    for (unsigned i = 0; i < sz / 2; i++)
    {
        int temp;
        temp = myvector[sz - 1 - i];
        myvector[sz - 1 - i] = myvector[i];
        myvector[i] = temp;
    }
    displayVect(myvector);

    return 0;
}