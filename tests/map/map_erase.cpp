#include "tests.tpp"

int main()
{
    NS::map<char, int> mymap;
    NS::map<char, int>::iterator it;

    mymap['a'] = 10;
    mymap['b'] = 20;
    mymap['c'] = 30;
    mymap['d'] = 40;
    mymap['e'] = 50;
    mymap['f'] = 60;
    //displayMap(mymap);
    mymap.tree_draw();

    it = mymap.find('b');
    mymap.erase(it); // erasing by iterator
    displayMap(mymap);

    mymap.erase('c'); // erasing by key
    displayMap(mymap);

    it = mymap.find('e');
    mymap.erase(it, mymap.end()); // erasing by range

    displayMap(mymap);

    mymap.erase(mymap.begin(), mymap.end()); // erasing by range
    displayMap(mymap);

    return 0;
}