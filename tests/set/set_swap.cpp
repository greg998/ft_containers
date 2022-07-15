#include "tests.tpp"

int main()
{
	int myints[] = {12, 75, 10, 32, 20, 25};
	NS::set<int> first(myints, myints + 3);		 // 10,12,75
	NS::set<int> second(myints + 3, myints + 6); // 20,25,32

	first.swap(second);

	std::cout << "first contains:";
	for (NS::set<int>::iterator it = first.begin(); it != first.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	std::cout << "second contains:";
	for (NS::set<int>::iterator it = second.begin(); it != second.end(); ++it)
		std::cout << ' ' << *it;
	std::cout << '\n';

	return 0;
}