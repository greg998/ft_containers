#include "tests.tpp"

int main()
{
	int myints[] = {16, 2, 77, 29, 42};
	NS::vector<int> myvector(myints, myints + sizeof(myints) / sizeof(int));


	NS::vector<int>::const_iterator it1 (myvector.begin());
	
	*it1 = 2;
	return (0);
}