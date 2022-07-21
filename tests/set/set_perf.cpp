#include "tests.tpp"

int main()
{
	NS::set<int> myset;


	for (int i = 0; i < 3000000; ++i)
		myset.insert(i);
	for (int i = 3000000 / 2; i >= 0; --i)
		myset.erase(i);
	return 0;
}
