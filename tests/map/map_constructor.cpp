#include "tests.tpp"

bool fncomp(char lhs, char rhs) { return lhs > rhs; }

struct classcomp
{
    bool operator()(const char &lhs, const char &rhs) const
    {
        return lhs > rhs;
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

    NS::map<char, int, classcomp> fourth;
    fourth['a'] = 10;
    fourth['b'] = 30;
    fourth['c'] = 50;
    fourth['d'] = 70;
    displayMap(fourth);

    bool (*fn_pt)(char, char) = fncomp;
    NS::map<char, int, bool (*)(char, char)> fifth(fn_pt);
    fifth['a'] = 10;
    fifth['b'] = 30;
    fifth['c'] = 50;
    fifth['d'] = 70;
    displayMap(fifth);
    return 0;
}