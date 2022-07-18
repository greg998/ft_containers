#include "tests.tpp"

int main()

{
    NS::map<char, int> mymap;

    // first insert function version (single parameter):
    mymap.insert(NS::pair<char, int>('a', 100));
    mymap.insert(NS::pair<char, int>('z', 200));

    NS::pair<NS::map<char, int>::iterator, bool> ret;
    ret = mymap.insert(NS::pair<char, int>('z', 500));
    if (ret.second == false)
    {
        std::cout << "element 'z' already existed";
        std::cout << " with a value of " << ret.first->second << '\n';
    }

    // second insert function version (with hint position):
    NS::map<char, int>::iterator it = mymap.begin();
    mymap.insert(it, NS::pair<char, int>('b', 300)); // max efficiency inserting
    mymap.insert(it, NS::pair<char, int>('c', 400)); // no max efficiency inserting

    // third insert function version (range insertion):
    NS::map<char, int> anothermap;
    anothermap.insert(mymap.begin(), mymap.find('c'));

    // showing contents:
    std::cout << "mymap contains:\n";
    for (it = mymap.begin(); it != mymap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';

    std::cout << "anothermap contains:\n";
    for (it = anothermap.begin(); it != anothermap.end(); ++it)
        std::cout << it->first << " => " << it->second << '\n';
    return 0;
}