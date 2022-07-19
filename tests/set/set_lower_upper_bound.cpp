#include "tests.tpp"

int main()
{
	NS::set<int> myset;
	NS::set<int>::iterator itlow, itup;

	for (int i = 1; i < 10; i++)
		myset.insert(i * 10); // 10 20 30 40 50 60 70 80 90
	displaySet(myset);

	itlow = myset.lower_bound(30); // 30
	itup = myset.upper_bound(60);  // 70

	myset.erase(itlow, itup); // 10 20 70 80 90

	displaySet(myset);

	return 0;
}