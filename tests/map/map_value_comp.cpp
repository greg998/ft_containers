#include "tests.tpp"

int main()
{
    NS::map<char, int> mymap;

    mymap['x'] = 1001;
    mymap['y'] = 2002;
    mymap['z'] = 3003;

    std::cout << "mymap contains:\n";

    NS::pair<char, int> highest = *mymap.rbegin(); // last element

    NS::map<char, int>::iterator it = mymap.begin();
    do
    {
        std::cout << it->first << " => " << it->second << '\n';
    } while (mymap.value_comp()(*it++, highest));

    return 0;
}