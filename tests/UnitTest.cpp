#include "UnitTest.hpp"

UnitTest::UnitTest(const std::string &category, const std::string &fname, bool shouldCompile)
    : _fname(fname), _path("tests/" + category + "/" + fname), _shouldCompile(shouldCompile)
{
}

UnitTest::UnitTest(std::string fname)
    : _fname(fname)
{
}

bool UnitTest::compile(const std::string &ns) const
{
    int st = 0;
    pid_t p = fork();
    if (!p)
    {
        if (ns == "ft")
        {
            char **const compile_arg = new char *[8];

            const char *const compile_arg_const[8] = {"c++", "-std=c++98", "-Wall", "-Wextra", "-Iincludes", "-DNS=ft", _path.c_str(), NULL};
            memcpy(compile_arg, compile_arg_const, sizeof(compile_arg_const));
            execvp("c++", compile_arg);
        }
        else
        {
            char **const compile_arg = new char *[8];

            const char *const compile_arg_const[8] = {"c++", "-std=c++98", "-Wall", "-Wextra", "-Iincludes", "-DNS=std", _path.c_str(), NULL};
            memcpy(compile_arg, compile_arg_const, sizeof(compile_arg_const));
            execvp("c++", compile_arg);
        }
        exit(2);
    }
    waitpid(p, &st, 0);
    std::cout << "here " << WEXITSTATUS(st) << std::endl;
    return (WEXITSTATUS(st) == 0);
}
void UnitTest::exec(void) const
{
    int st = 0;
    pid_t p = fork();
    if (!p)
    {
        char **const args = new char *[1];
        *args = NULL;
        execvp("./a.out", args);
        exit(4);
    }
    waitpid(p, &st, 0);
}

bool UnitTest::operator==(const UnitTest &rhs) const
{
    return (_fname == rhs._fname);
}
bool UnitTest::operator<(const UnitTest &rhs) const
{
    return (_fname < rhs._fname);
}