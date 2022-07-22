#include "Tester.hpp"

Tester::Tester() : _testTime(0), _refTime(0)
{
}

void Tester::addTest(const std::string &category, const std::string &fname, bool shouldCompile)
{
    this->_tests[category].push_back(UnitTest(category, fname, shouldCompile));
}

Tester::test_vect::iterator Tester::runTest(const std::string &category, const std::string &fname, const std::string &ns)
{
    category_map::iterator it(_tests.find(category));
    if (it == _tests.end())
        throw TestException("Category " + category + " not found");
    test_vect::iterator it2 = find(it->second.begin(), it->second.end(), fname);
    if (it2 == it->second.end())
        throw TestException("Test " + fname + " not found");
    if (it2->compile(ns))
        it2->exec();
    return (it2);
}

void Tester::runCategory(const std::string &category)
{
    category_map::iterator it(_tests.find(category));
    if (it == _tests.end())
        throw TestException("Category " + category + " not found");
    test_vect &t(it->second);

    for (test_vect::iterator it2 = t.begin(); it2 != t.end(); ++it2)
    {
        if (it2->compile(std::string(NS)))
            it2->exec();
    }
}

void Tester::runAll(void)
{
    for (category_map::iterator it = _tests.begin(); it != _tests.end(); ++it)
    {
        for (test_vect::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            if (it2->compile(std::string(NS)))
                it2->exec();
        }
    }
}

void Tester::compareTo(const std::string &category, const std::string &fname, const std::string &ns)
{
    test_vect::iterator toTest = runTest(category, fname);
    compareTo(toTest, category, ns);
}

void Tester::compareTo(test_vect::iterator toTest, const std::string &category, const std::string &ns)
{
    UnitTest ref(*toTest);
    if (ref.compile(ns))
        ref.exec();

    std::cout << std::left << std::setw(25) << toTest->getFname() << ": ";
    std::cout << "compile: ";
    if (toTest->compile())
        std::cout << ("[OK]");
    else
        std::cout << ("[KO]");
    if (toTest->getSig())
    {
        std::cout << " " << sigToStr(toTest->getSig());
    }
    else
    {
        std::cout << " diff:";
        if ((toTest->getOutput() == ref.getOutput() && toTest->compile())
            || (!toTest->compile() && !ref.compile()))
        {
            _passed[category]++;
            if (toTest->compile() && ref.compile())
            {
                _testTime += toTest->getExecTime();
                _refTime += ref.getExecTime();
            }
            std::cout << " [OK] ";
        }
        else
            std::cout << " [KO] ";
        std::cout << toTest->getExecTime() << "s ";
        std::cout << ref.getExecTime() << "s ";
    }
    std::cout << '\n';
}

const char *Tester::sigToStr(int sig)
{
    if (sig == SIGBUS)
        return ("[SIGBUS]");
    else if (sig == SIGSEGV)
        return ("[SIGSEGV]");
    return ("[SIG]");
}

void Tester::compareCategoryTo(const std::string &category, const std::string &ns)
{
    category_map::iterator it(_tests.find(category));
    if (it == _tests.end())
        throw TestException("Category " + category + " not found");
    test_vect &t(it->second);

    std::cout << "---------------------" << std::endl;
    for (test_vect::iterator it2 = t.begin(); it2 != t.end(); ++it2)
    {
        if (it2->compile(std::string(NS)))
            it2->exec();
        compareTo(it2, category, ns);
    }
    std::cout << _passed[category] << " / " << t.size() << " passed" << std::endl;
    std::cout << NS << " time: " << _testTime << "s " << ns << " time: " << _refTime << "s" << std::endl;

    if (_testTime <= _refTime)
    {
        double percent = _refTime / _testTime;
        std::cout << NS << " is " << percent << " times faster than " << ns << std::endl;
    }
    else
    {
        double percent = _testTime / _refTime;
        std::cout << NS << " is " << percent << " times slower than " << ns << std::endl;
    }
}

void Tester::compareAllTo(const std::string &ns)
{
    for (category_map::iterator it = _tests.begin(); it != _tests.end(); ++it)
    {
        compareCategoryTo(it->first, ns);
        _refTime = 0;
        _testTime = 0;
    }
}