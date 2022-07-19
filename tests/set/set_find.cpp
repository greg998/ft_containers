#include "tests.tpp"

int main()
{
	NS::set<int> myset;
	NS::set<int>::iterator it;

	// set some initial values:
	for (int i = 1; i <= 5; i++)
		myset.insert(i * 10); // set: 10 20 30 40 50
	displaySet(myset);

	it = myset.find(20);
	myset.erase(it);
	displaySet(myset);
	myset.erase(myset.find(40));

	displaySet(myset);

	return 0;
}