#include "tests.tpp"

int main()
{
	int myints[] = {21, 64, 17, 78, 49};
	NS::set<int> myset(myints, myints + 5);

	NS::set<int>::reverse_iterator rit;

	std::cout << "myset contains:";
	for (rit = myset.rbegin(); rit != myset.rend(); ++rit)
		std::cout << ' ' << *rit;

	std::cout << '\n';

	return 0;
}