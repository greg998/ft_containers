#include "tests.tpp"

int main()
{
	NS::stack<int> st;

	for (int i = 0; i < 10000000; ++i)
		st.push(i);
	
	for (int i = 0; i < 10000000; ++i)
		st.pop();
	return (0);
}