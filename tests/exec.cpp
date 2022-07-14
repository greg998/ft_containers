#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <iostream>
#include <string.h>

int main(int argc, char **argv)
{
    if (argc == 1 || argc > 3)
        return (3);

    pid_t p = fork();
    int st = 0;
    int ret;
    if (!p)
    {
        if (argc == 2)
        {
            char **const compile_arg = new char *[7];

            const char *const compile_arg_const[7] = {"c++", "-std=c++98", "-Wall", "-Wextra", "-I../includes", argv[1], NULL};
            memcpy(compile_arg, compile_arg_const, sizeof(compile_arg_const));
            execvp("c++", compile_arg);
        }
        else
        {
            char **const compile_arg = new char *[8];

            const char *const compile_arg_const[8] = {"c++", "-std=c++98", "-Wall", "-Wextra", "-I../includes", "-DNS=STD", argv[1], NULL};
            memcpy(compile_arg, compile_arg_const, sizeof(compile_arg_const));
            execvp("c++", compile_arg);
        }
        exit(2);
    }

    waitpid(p, &st, 0);
    ret = WEXITSTATUS(st);
    if (ret > 0)
        return (ret);

    p = fork();
    if (!p)
    {
        char **const args = new char *[1];
        *args = NULL;
        if (execvp("./a.out", args) == -1)
            exit(4);
    }
    waitpid(p, &st, 0);
    ret = WEXITSTATUS(st);
    return (ret);
}