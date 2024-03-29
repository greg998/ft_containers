#include "tests.tpp"

int main()
{
    {
        NS::vector<int> foo(3, 100); // three ints with a value of 100
        NS::vector<int> bar(2, 200); // two ints with a value of 200
        displayVect(foo);
        displayVect(bar);

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
    {
        NS::vector<int> foo(3, 100); // three ints with a value of 100
        NS::vector<int> bar(3, 100); // two ints with a value of 200
        displayVect(foo);
        displayVect(bar);

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