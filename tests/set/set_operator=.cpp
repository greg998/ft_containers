#include "tests.tpp"

bool fncomp(int lhs, int rhs) { return lhs > rhs; }

struct classcomp
{
	bool operator()(const int &lhs, const int &rhs) const
	{
		return lhs > rhs;
	}
};

int main()
{
	int myints[] = {12, 82, 37, 64, 15};
	NS::set<int> first(myints, myints + 5); // set with 5 ints
	NS::set<int> second;					// empty set
	displaySet(first);
	displaySet(second);

	second = first;			// now second contains the 5 ints
	first = NS::set<int>(); // and first is empty

	displaySet(first);
	displaySet(second);
	return 0;
}