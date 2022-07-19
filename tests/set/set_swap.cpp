#include "tests.tpp"

int main()
{
	int myints[] = {12, 75, 10, 32, 20, 25};
	NS::set<int> first(myints, myints + 3);		 // 10,12,75
	NS::set<int> second(myints + 3, myints + 6); // 20,25,32
	displaySet(first);
	displaySet(second);

	first.swap(second);

	displaySet(first);
	displaySet(second);

	NS::swap(first, second);
	displaySet(first);
	displaySet(second);
	return 0;
}