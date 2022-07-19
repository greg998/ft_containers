#include "tests.tpp"

int main()
{
    NS::map<char, int> mymap;

    mymap['x'] = 100;
    mymap['y'] = 200;
    mymap['z'] = 300;

    std::cout << "mymap contains:\n";
    displayMap(mymap);

    mymap.clear();
    mymap['a'] = 1101;
    mymap['b'] = 2202;

    std::cout << "mymap contains:\n";
    displayMap(mymap);

    return 0;
}