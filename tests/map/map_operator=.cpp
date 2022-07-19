#include "tests.tpp"

int main()
{
    NS::map<char, int> first;
    NS::map<char, int> second;

    first['x'] = 8;
    first['y'] = 16;
    first['z'] = 32;
    displayMap(first);
    displayMap(second);


    second = first;               // second now contains 3 ints
    first = NS::map<char, int>(); // and first is now empty

    displayMap(first);
    displayMap(second);
    return 0;
}