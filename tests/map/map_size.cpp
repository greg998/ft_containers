#include "tests.tpp"

int main()
{
    NS::map<char, int> mymap;
    mymap['a'] = 101;
    mymap['b'] = 202;
    mymap['c'] = 302;

    std::cout << "mymap.size() is " << mymap.size() << '\n';

    return 0;
}