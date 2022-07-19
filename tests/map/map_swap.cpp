#include "tests.tpp"

int main()
{
    NS::map<char, int> foo, bar;

    foo['x'] = 100;
    foo['y'] = 200;

    bar['a'] = 11;
    bar['b'] = 22;
    bar['c'] = 33;

    foo.swap(bar);

    std::cout << "foo contains:\n";
    displayMap(foo);

    std::cout << "bar contains:\n";
    displayMap(bar);

    NS::swap(foo, bar);
    displayMap(foo);
    displayMap(bar);
    return 0;
}