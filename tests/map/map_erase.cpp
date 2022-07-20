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
    displayMap(mymap);

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

    // {
    //     NS::map<int, int> m;

    //     m[3] = 1;
    //     m[21] = 1;
    //     m[32] = 1;
    //     m[15] = 1;
    //     m[31] = 1;
    //     m[0] = 1;
    //     m[19] = 1;
    //     m.tree_draw("tree");
    //     m.erase(0);
    //     m.tree_draw("0"); // case a)iii

    // }
    // {
    //     NS::map<int, int> m;

    //     m[3] = 1;
    //     m[21] = 1;
    //     m[32] = 1;
    //     m[15] = 1;
    //     m[31] = 1;
    //     m[0] = 1;
    //     m[14] = 1;
    //     m.tree_draw("tree");

    //     m.erase(0);
    //     m.tree_draw("0"); // case a)iv
    // }
    // {
    //     NS::map<int, int> m;

    //     m[3] = 1;
    //     m[21] = 1;
    //     m[32] = 1;
    //     m[15] = 1;
    //     m[31] = 1;
    //     m[0] = 1;
    //     m[-1] = 1;
    //     m.tree_draw("tree");

    //     m.erase(15);
    //     m.tree_draw("15"); // case a)i
    // }
    // {
    //     NS::map<int, int> m;

    //     m[3] = 1;
    //     m[21] = 1;
    //     m[32] = 1;
    //     m[15] = 1;
    //     m[31] = 1;
    //     m[0] = 1;
    //     m[1] = 1;
    //     m.tree_draw("tree");

    //     m.erase(15);
    //     m.tree_draw("15"); // case a)ii

    //     m.erase(3); // case b) recolour
    //     m.tree_draw("3");
    // }
    // {
    //     NS::map<int, int> m;

    //     m[3] = 1;
    //     m[21] = 1;
    //     m[32] = 1;
    //     m[15] = 1;
    //     m[0] = 1;
    //     m[1] = 1;
    //     m.tree_draw("tree");

    //     m.erase(32); // case c)i
    //     m.tree_draw("32");
    // }
    return 0;
}