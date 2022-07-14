#ifndef TESTER_HPP
#define TESTER_HPP
#include <iostream>
#include "UnitTest.hpp"
#include <set>
#include <map>

#ifndef NS
#define NS "ft"
#endif

class Tester
{
public:
    typedef std::set<UnitTest> set_type;
    typedef std::map<const std::string, set_type> map_type;

private:
    map_type _tests;

public:
    void addTest(const std::string &category, const std::string &fname, bool shouldCompile);

    void runTest(const std::string &category, const std::string &fname) const;
    void runCategory(const std::string &category) const;
    void runAll(void) const;
};
#endif