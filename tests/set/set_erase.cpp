#include "tests.tpp"

int main()
{
	NS::set<int> myset;
	NS::set<int>::iterator it;

	// insert some values:
	for (int i = 1; i < 10; i++)
		myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90
	displaySet(myset);

	it = myset.begin();
	++it; // "it" points now to 20

	myset.erase(it);
	displaySet(myset);

	myset.erase(40);
	displaySet(myset);

	it = myset.find(60);
	myset.erase(it, myset.end());
	displaySet(myset);

	return 0;
}