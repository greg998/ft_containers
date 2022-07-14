#ifndef UNITTEST_HPP
#define UNITTEST_HPP
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>

class UnitTest
{
private:
    std::string _fname;
    std::string _path;
    bool    _shouldCompile;
public:
    UnitTest(const std::string &category, const std::string &fname, bool shouldCompile);
    UnitTest(std::string fname);

    void    exec(void) const;
    bool    compile(const std::string &ns) const;

    bool operator==(const UnitTest &rhs) const;
    bool operator<(const UnitTest &rhs) const;

};

#endif