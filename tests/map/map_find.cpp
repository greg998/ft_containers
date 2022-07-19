#include "tests.tpp"

int main()
{
    NS::map<char, int> mymap;
    NS::map<char, int>::iterator it;

    mymap['a'] = 50;
    mymap['b'] = 100;
    mymap['c'] = 150;
    mymap['d'] = 200;

    it = mymap.find('b');
    if (it != mymap.end())
        mymap.erase(it);

    displayMap(mymap);

    it = mymap.find('e');
    if (it == mymap.end())
        std::cout << "e not found\n";
    return 0;
}