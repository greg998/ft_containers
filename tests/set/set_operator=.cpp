#include "tests.tpp"

bool fncomp(int lhs, int rhs) { return lhs < rhs; }

struct classcomp
{
	bool operator()(const int &lhs, const int &rhs) const
	{
		return lhs < rhs;
	}
};

int main()
{
	NS::set<int> first; // empty set of ints

	int myints[] = {10, 20, 30, 40, 50};
	NS::set<int> second(myints, myints + 5); // range

	NS::set<int> third(second); // a copy of second

	NS::set<int> fourth(second.begin(), second.end()); // iterator ctor.

	NS::set<int, classcomp> fifth; // class as Compare

	bool (*fn_pt)(int, int) = fncomp;
	NS::set<int, bool (*)(int, int)> sixth(fn_pt); // function pointer as Compare

	return 0;
}