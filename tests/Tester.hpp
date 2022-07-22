#ifndef TESTER_HPP
#define TESTER_HPP
#include <iostream>
#include "UnitTest.hpp"
#include <vector>
#include <map>
#include <algorithm>
#include <iomanip>

#ifndef NS
#define NS "ft"
#endif

class Tester
{
public:
    typedef std::vector<UnitTest> test_vect;
    typedef std::map<const std::string, test_vect> category_map;
    typedef std::map<const std::string, int> passed_map;

private:
    category_map _tests;
    passed_map _passed;

    double _testTime;
    double _refTime;

public:
    Tester();

    void addTest(const std::string &category, const std::string &fname, bool shouldCompile);

    test_vect::iterator runTest(const std::string &category, const std::string &fname, const std::string &ns = NS);
    void runCategory(const std::string &category);
    void runAll(void);
    void compareTo(const std::string &category, const std::string &fname, const std::string &ns);
    void compareTo(test_vect::iterator toTest, const std::string &category, const std::string &ns);
    void compareAllTo(const std::string &ns);
    void compareCategoryTo(const std::string &category, const std::string &ns);

    static const char *sigToStr(int sig);

    class TestException : public std::runtime_error
    {
    public:
        TestException(const std::string &error)
            : std::runtime_error(error.c_str())
        {
        }
    };
};
#endif