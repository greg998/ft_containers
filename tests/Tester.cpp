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
    test_vect::iterator referee = runTest(category, fname, ns);
    _testTime += toTest->getExecTime();
    _refTime += referee->getExecTime();
    printLineResult(toTest, referee);
}

const   char *sigToStr(int sig)
{
    if (sig == SIGBUS)
        return ("[SIGBUS]");
    else if (sig == SIGSEGV)
        return ("[SIGSEGV]");
    return ("[SIG]");
}

void Tester::printLineResult(test_vect::iterator toTest, test_vect::iterator ref)
{
    std::cout << toTest->getFname() << ": ";
    if (toTest->compile())
        std::cout << ("compile ok");
    else
        std::cout << ("compile fail");
    if (toTest->getSig())
    {
        std::cout << sigToStr(toTest->getSig());
    }
    else
    {
        if (toTest->getOutput() == ref->getOutput())
            std::cout << " [OK] ";
        else
            std::cout << " [BAD] ";
        std::cout << toTest->getExecTime() << " ";
        std::cout << ref->getExecTime();
    }
    std::cout << '\n';
}