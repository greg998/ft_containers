#include "tests.tpp"

int main()
{
    {
        NS::map<char, int> foo, bar;
        foo['a'] = 100;
        foo['b'] = 200;
        bar['a'] = 10;
        bar['z'] = 1000;

        if (foo == bar)
            std::cout << "foo and bar are equal\n";
        if (foo != bar)
            std::cout << "foo and bar are not equal\n";
        if (foo < bar)
            std::cout << "foo is less than bar\n";
        if (foo > bar)
            std::cout << "foo is greater than bar\n";
        if (foo <= bar)
            std::cout << "foo is less than or equal to bar\n";
        if (foo >= bar)
            std::cout << "foo is greater than or equal to bar\n";
    }
    std::cout << "-----------------------\n";
    {
        NS::map<char, int> foo, bar;
        foo['a'] = 100;
        foo['b'] = 1000;
        bar['a'] = 100;
        bar['b'] = 1000;

        if (foo == bar)
            std::cout << "foo and bar are equal\n";
        if (foo != bar)
            std::cout << "foo and bar are not equal\n";
        if (foo < bar)
            std::cout << "foo is less than bar\n";
        if (foo > bar)
            std::cout << "foo is greater than bar\n";
        if (foo <= bar)
            std::cout << "foo is less than or equal to bar\n";
        if (foo >= bar)
            std::cout << "foo is greater than or equal to bar\n";
    }

    return 0;
}