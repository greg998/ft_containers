#include "tests.tpp"

int main()
{
	NS::map<int, int> mymap;


	for (int i = 0; i < 3000000; ++i)
		mymap[i] = i;
	for (int i = 3000000 / 2; i >= 0; --i)
		mymap.erase(i);
	std::cout << "good\n";
	return 0;
}