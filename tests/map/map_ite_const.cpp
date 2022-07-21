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

	NS::map<char, int>::const_iterator it1 (mymap.begin());
	it1->second = 2;

	return (0);
}