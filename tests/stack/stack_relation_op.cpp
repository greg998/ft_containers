#include "tests.tpp"

int main()
{
    {
        NS::stack<int> foo, bar;
        foo.push(100);
        foo.push(200);
        bar.push(10);
        bar.push(1000);

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
    std::cout << "--------------------\n";
    {
        NS::stack<int> foo, bar;
        foo.push(100);
        foo.push(200);
        bar.push(100);
        bar.push(200);

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