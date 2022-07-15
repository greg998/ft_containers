#include "tests.tpp"

int main()
{
	NS::set<int> myset;

	NS::set<int>::value_compare mycomp = myset.value_comp();

	for (int i = 0; i <= 5; i++)
		myset.insert(i);

	std::cout << "myset contains:";

	int highest = *myset.rbegin();
	NS::set<int>::iterator it = myset.begin();
	do
	{
		std::cout << ' ' << *it;
	} while (mycomp(*(++it), highest));

	std::cout << '\n';

	return 0;
}