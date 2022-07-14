#include "tests.tpp"

int main()
{
    NS::map<char, int> mymap;

    mymap['b'] = 100;
    mymap['a'] = 200;
    mymap['c'] = 300;

    // show content:
    for (NS::map<char, int>::iterator it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    return 0;
}