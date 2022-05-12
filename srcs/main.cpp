#include <iostream>
#include <string>

#include <stdlib.h>
#include "vector.tpp"
#include <vector>
#include <cstdlib>
#include <new>
#include <limits>
#include <iostream>
#include <vector>


int main(int argc, char** argv) {
	std::vector<int> ve(5,2);
	const int c= 2;
	ft::vector<int> vect (5,2);
	for (int i = 0; i < 5; ++i)
	{
		std::cout << vect[i] << " ";
	}
	std::cout << std::endl;
	std::cout << vect.max_size() << std::endl;
	std::cout << ve.max_size() << std::endl;
	std::cout << "sizeof vector " << sizeof(ve) << std::endl;
	std::cout << "sizeof ft vector " << sizeof(vect) << std::endl;
	return (0);
}