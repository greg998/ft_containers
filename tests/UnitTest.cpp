#include "UnitTest.hpp"

UnitTest::UnitTest(const std::string &category, const std::string &fname, bool shouldCompile)
    : _fname(fname), _path("tests/" + category + "/" + fname), _shouldCompile(shouldCompile), _sig(0)
{
    bzero(fds, sizeof(fds));
}

UnitTest::UnitTest(std::string fname)
    : _fname(fname), _sig(0)
{
    bzero(fds, sizeof(fds));
}

UnitTest::~UnitTest()
{
    close_fds();
}

UnitTest::UnitTest(const UnitTest &src) : _fname(src._fname), _path(src._path), _shouldCompile(src._shouldCompile), _compile(src._compile), _execTime(src._execTime), _sig(0)
{
    bzero(fds, sizeof(fds));
}

void UnitTest::close_fds()
{
    if (fds[0] > 0)
        close(fds[0]);
    if (fds[1] > 0)
        close(fds[1]);
}

bool UnitTest::compile(const std::string &ns)
{
    int st = 0;
    pid_t p = fork();
    if (!p)
    {
        char **const compile_arg = new char *[8];

        const char *const compile_arg_const[] = {"c++", "-std=c++98", "-Wall", "-Wextra", "-Iincludes", ("-DNS=" + ns).c_str(), _path.c_str(), NULL};
        memcpy(compile_arg, compile_arg_const, sizeof(compile_arg_const));
        execvp("c++", compile_arg);

        exit(2);
    }
    waitpid(p, &st, 0);
    _compile = WEXITSTATUS(st) == 0;
    return (_compile);
}
void UnitTest::exec()
{
    int st;
    struct timespec s, e;

    close_fds();
    if (pipe(fds) == -1)
        throw TestException("pipe: " + std::string(strerror(errno)));
    clock_gettime(CLOCK_MONOTONIC, &s);

    pid_t p = fork();
    if (p == -1)
        throw TestException("fork: " + std::string(strerror(errno)));
    if (!p)
    {
        dup2(fds[1], 1);
        close(fds[0]);
        char **const args = new char *[3];
        const char *const arg_const[3] = {"valgrind", "./a.out", NULL};
        memcpy(args, arg_const, sizeof(arg_const));
        execvp("./a.out", args);
        // execvp("valgrind", args);
        free(args);
        exit(1);
    }
    waitpid(p, &st, 0);
    if (WIFSIGNALED(st))
        _sig = WTERMSIG(st);
    else
    {
        clock_gettime(CLOCK_MONOTONIC, &e);
        _execTime = (double)(e.tv_sec - s.tv_sec) + (double)(e.tv_nsec - s.tv_nsec) / 1e+9;
        readOutput();
#ifndef CMP
        std::cout << _output;
#endif
    }
}

void UnitTest::readOutput()
{
    int ret;
    char buf[BUFFER_SIZE];

    bzero(buf, BUFFER_SIZE);
    close(fds[1]);
    while ((ret = read(fds[0], buf, BUFFER_SIZE)) > 0)
        _output.append(buf);
    close(fds[0]);
    if (ret == -1)
        throw TestException("read: " + std::string(strerror(errno)));
}

bool UnitTest::compile() const
{
    return (_compile);
}

double UnitTest::getExecTime() const
{
    return (_execTime);
}

const std::string &UnitTest::getFname() const
{
    return (_fname);
}

const std::string &UnitTest::getOutput() const
{
    return (_output);
}

double UnitTest::getSig() const
{
    return (_sig);
}

bool UnitTest::operator==(const UnitTest &rhs) const
{
    return (_fname == rhs._fname);
}
bool UnitTest::operator<(const UnitTest &rhs) const
{
    return (_fname < rhs._fname);
}