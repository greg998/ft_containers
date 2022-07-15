#include "tests.tpp"

int main()
{
	int myints[] = {75, 23, 65, 42, 13};
	NS::set<int> myset(myints, myints + 5);

	std::cout << "myset contains:";
	for (NS::set<int>::iterator it = myset.begin(); it != myset.end(); ++it)
		std::cout << ' ' << *it;

	std::cout << '\n';

	return 0;
}