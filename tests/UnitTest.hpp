#ifndef UNITTEST_HPP
#define UNITTEST_HPP
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <fstream>
#include <sys/times.h>
#include <sys/resource.h>
#include <stdio.h>
#include <time.h>
#define BUFFER_SIZE 2048

class UnitTest
{
private:
    std::string _fname;
    std::string _path;
    bool _shouldCompile;
    bool _compile;
    double _execTime;
    std::string _output;
    int fds[2];
    int _sig;

public:
    UnitTest(const std::string &category, const std::string &fname, bool shouldCompile);
    UnitTest(const UnitTest &src);
    UnitTest(std::string fname);
    ~UnitTest();

    void exec();
    bool compile(const std::string &ns);
    bool compile() const;
    void readOutput();
    void close_fds();
    double getExecTime() const;
    const std::string &getFname() const;
    double getSig() const;
    const std::string &getOutput() const;

    bool operator==(const UnitTest &rhs) const;
    bool operator<(const UnitTest &rhs) const;

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