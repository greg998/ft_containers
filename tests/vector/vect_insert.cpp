#include "tests.tpp"

int main()
{
    NS::vector<int> myvector(3, 100);
    NS::vector<int>::iterator it;

    it = myvector.begin();
    it = myvector.insert(it, 200);
    displayVect(myvector);

    myvector.insert(it, 200, 300);
    displayVect(myvector);

    // "it" no longer valid, get a new one:
    it = myvector.begin();

    NS::vector<int> anothervector(2, 400);
    myvector.insert(it + 2, anothervector.begin(), anothervector.end());
    displayVect(myvector);

    int myarray[] = {501, 502, 503};
    myvector.insert(myvector.begin(), myarray, myarray + 3);
    displayVect(myvector);

    NS::vector<int> anothervector2;
    anothervector2.insert(anothervector2.begin(), myvector.begin(), myvector.end());
    displayVect(anothervector2);

    return 0;
}