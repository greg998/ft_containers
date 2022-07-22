#include "tests.tpp"

int main()
{
	NS::vector<int> vect;

	for (int i = 0; i < 10000000; ++i)
		vect.push_back(i);
	
	for (int i = 0; i < 10000000; ++i)
		vect.pop_back();
	std::cout << "good\n";
	
	return (0);
}