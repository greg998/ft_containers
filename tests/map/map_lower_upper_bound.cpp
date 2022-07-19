#include "tests.tpp"

int main()
{
    NS::map<char, int> mymap;
    NS::map<char, int>::iterator itlow, itup;

    mymap['a'] = 20;
    mymap['b'] = 40;
    mymap['c'] = 60;
    mymap['d'] = 80;
    mymap['e'] = 100;

    itlow = mymap.lower_bound('b'); // itlow points to b
    itup = mymap.upper_bound('d');  // itup points to e (not d!)

    mymap.erase(itlow, itup); // erases [itlow,itup)

    displayMap(mymap);

    return 0;
}