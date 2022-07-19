#include "tests.tpp"

int main()
{
	NS::set<int> myset;

	for (int i = 1; i <= 5; i++)
		myset.insert(i * 10); // myset: 10 20 30 40 50
	displaySet(myset);

	NS::pair<NS::set<int>::const_iterator, NS::set<int>::const_iterator> ret;
	ret = myset.equal_range(30);

	std::cout << "the lower bound points to: " << *ret.first << '\n';
	std::cout << "the upper bound points to: " << *ret.second << '\n';

	return 0;
}