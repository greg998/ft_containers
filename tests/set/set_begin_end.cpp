#include "tests.tpp"

int main()
{
	int myints[] = {75, 23, 65, 42, 13};
	NS::set<int> myset(myints, myints + 5);

	std::cout << "myset contains:\n";
	displaySet(myset);

	return 0;
}