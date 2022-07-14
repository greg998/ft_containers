#include "tests.tpp"

bool fncomp(char lhs, char rhs) { return lhs < rhs; }

struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs < rhs;
    }
};

int main()
{
    NS::map<char, int> first;

    first['a'] = 10;
    first['b'] = 30;
    first['c'] = 50;
    first['d'] = 70;

    NS::map<char, int> second(first.begin(), first.end());
    displayMap(second);

    NS::map<char, int> third(second);
    displayMap(third);

    NS::map<char, int, classcomp> fourth; // class as Compare
    displayMap(fourth);

    bool (*fn_pt)(char, char) = fncomp;
    NS::map<char, int, bool (*)(char, char)> fifth(fn_pt); // function pointer as Compare
    displayMap(fifth);
    return 0;
}