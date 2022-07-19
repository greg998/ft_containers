#include "tests.tpp"

int main()
{
	NS::set<int> myset;

	myset.insert(100);
	myset.insert(200);
	myset.insert(300);

	displaySet(myset);

	myset.clear();
	myset.insert(1101);
	myset.insert(2202);

	displaySet(myset);

	return 0;
}