#include "tests.tpp"

int main()
{
	NS::set<int> myset;
	int highest;

	NS::set<int>::key_compare mycomp = myset.key_comp();

	for (int i = 0; i <= 5; i++)
		myset.insert(i);

	std::cout << "myset contains:";

	highest = *myset.rbegin();
	NS::set<int>::iterator it = myset.begin();
	do
	{
		std::cout << ' ' << *it;
	} while (mycomp(*(++it), highest));

	std::cout << '\n';

	return 0;
}