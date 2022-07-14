#include "Tester.hpp"

void Tester::addTest(const std::string &category, const std::string &fname, bool shouldCompile)
{
    this->_tests[category].insert(UnitTest(category, fname, shouldCompile));
}

void Tester::runTest(const std::string &category, const std::string &fname) const
{
     map_type::const_iterator it (_tests.find(category));
    if (it == _tests.end())
        return ;
    set_type::iterator it2 = it->second.find(fname);
    if (it2->compile(std::string(NS)))
        it2->exec();
    std::cout << NS;
}

void Tester::runCategory(const std::string &category) const
{
    map_type::const_iterator it (_tests.find(category));
    if (it == _tests.end())
        return ;
    const set_type & t(it->second);

    for (set_type::iterator it2 = t.begin(); it2 != t.end(); ++it2)
    {
        if (it2->compile(std::string(NS)))
            it2->exec();
    }
}

void Tester::runAll(void) const
{
    for (map_type::const_iterator it = _tests.begin(); it != _tests.end(); ++it)
    {
        for (set_type::iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            if (it2->compile(std::string(NS)))
                it2->exec();
        }
    }
}
