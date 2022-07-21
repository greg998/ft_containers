#include "tests.tpp"

int main()
{
	int myints[] = {16, 2, 77, 29, 42};
	NS::vector<int> myvector(myints, myints + sizeof(myints) / sizeof(int));


	NS::vector<int>::iterator it1 (myvector.begin());
	
	*it1 = 5;
	std::cout << *it1 << "\n";
	it1++;
	std::cout << *it1 << "\n";
	it1--;
	std::cout << *it1 << "\n";
	it1--;
	std::cout << *it1 << "\n";
	it1++;
	std::cout << *it1 << "\n";

	++it1;
	std::cout << *it1 << "\n";
	++it1;
	std::cout << *it1 << "\n";
	--it1;
	std::cout << *it1 << "\n";
	++it1;
	std::cout << *it1 << "\n";


	NS::vector<int>::iterator it2 (it1);
	std::cout << *it2 << "\n";

	std::cout << *(it2 + 2) << "\n";
	std::cout << *(it2 - 2) << "\n";
	std::cout << *(2 + it2) << "\n";

	it2 += 2;
	std::cout << *it2 << "\n";
	it2 -= 2;
	std::cout << *it2 << "\n";
	std::cout << it2[2] << "\n";
	std::cout << (it1 < it2) << "\n";
	std::cout << (it1 > it2) << "\n";
	std::cout << (it1 <= it2) << "\n";
	std::cout << (it1 >= it2) << "\n";
	std::cout << (it1 == it2) << "\n";
	std::cout << (it1 != it2) << "\n";

	return (0);
}