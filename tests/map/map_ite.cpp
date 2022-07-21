#include "tests.tpp"

int main()
{
	NS::map<char, int> mymap;

	mymap['a'] = 10;
    mymap['b'] = 30;
    mymap['c'] = 50;
    mymap['x'] = 70;
    mymap['n'] = 70;
    mymap['u'] = 70;

	NS::map<char, int>::iterator it1 (mymap.begin());
	it1->second = 2;
	std::cout << it1->second << "\n";
	it1++;
	std::cout << it1->first << "\n";
	it1--;
	std::cout << it1->first << "\n";
	it1--;
	std::cout << it1->first << "\n";
	it1++;
	std::cout << it1->first << "\n";

	++it1;
	std::cout << it1->first << "\n";
	++it1;
	std::cout << it1->first << "\n";
	--it1;
	std::cout << it1->first << "\n";
	++it1;
	std::cout << it1->first << "\n";


	NS::map<char, int>::iterator it2 (it1);
	std::cout << it2->first << "\n";

	return (0);
}