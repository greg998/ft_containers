#include "tests.tpp"

int main()
{
    NS::map<char, int> mymap;

    mymap['x'] = 100;
    mymap['y'] = 200;
    mymap['z'] = 300;

    // show content:
    NS::map<char, int>::reverse_iterator rit;
    for (rit = mymap.rbegin(); rit != mymap.rend(); ++rit)
        std::cout << rit->first << " => " << rit->second << '\n';

    return 0;
}