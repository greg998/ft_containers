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

    displayMap(mymap);
    displayMap(anothermap);

    //all insert case test
    //NS::map<int, int> m;
    
    // m[3] = 1;
    // m[21] = 1;
    // m[32] = 1;
    // m.tree_draw("32");
    // m[15] = 1;
    // m.tree_draw("15"); // uncle is red -> recolour parent black and grandparent red

    // m[18] = 1;
    // m.tree_draw("18"); // uncle is black, p is right child of g, x(18) is right child of p -> left rotate gp(3)

    // m[14] = 1;
    // m.tree_draw("14"); // uncle is black, p is right child of g, x(14) is left child of p -> right rotate p(15) and left rotate gp(3)
    // ------
    // m[3] = 1;
    // m[21] = 1;
    // m[32] = 1;
    // m.tree_draw("32");
    // m[1] = 1;
    // m.tree_draw("1"); // uncle is red -> recolour parent black and grandparent red

    // m[2] = 1;
    // m.tree_draw("2"); // uncle is black, p(1) is left child of g, x(2) is right child of p -> left rotate p(1) and right rotate gp(3)

    // m[0] = 1;
    // m.tree_draw("0"); // uncle is black, p(1) is left child of g, x(0) is left child of p -> right rotate gp(3)

    return 0;
}