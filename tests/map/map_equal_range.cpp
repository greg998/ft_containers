#include "tests.tpp"

int main()
{
    NS::map<char, int> mymap;

    mymap['e'] = 30;
    mymap['a'] = 10;
    mymap['b'] = 20;
    displayMap(mymap);

    NS::pair<NS::map<char, int>::iterator, NS::map<char, int>::iterator> ret;
    ret = mymap.equal_range('b');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';
    
    ret = mymap.equal_range('c');

    std::cout << "lower bound points to: ";
    std::cout << ret.first->first << " => " << ret.first->second << '\n';

    std::cout << "upper bound points to: ";
    std::cout << ret.second->first << " => " << ret.second->second << '\n';

    return 0;
}