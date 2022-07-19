#include "tests.tpp"

int main()
{
    NS::map<char, int> mymap;

    mymap['b'] = 100;
    mymap['a'] = 200;
    mymap['c'] = 300;

    displayMap(mymap);
    //mymap.tree_draw();

    return 0;
}