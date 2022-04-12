#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>

extern char **environ;

void execute_program(char **args) {
    pid_t pid;
    if (posix_spawn(&pid, args[0], NULL, NULL, args, environ) != 0) {
        perror("posix_spawn");
        exit(1);
    }

    int status;
    if (waitpid(pid, &status, 0) == -1) {
        perror("waitpid");
        exit(1);
    }
}

int main(void) {
    execute_program((char *[]){"/bin/date", "+%d-%m-%Y", NULL});
    execute_program((char *[]){"/bin/data", "+%T", NULL});
    execute_program((char *[]){"/usr/bin/whoami", NULL});
    execute_program((char *[]){"/bin/hostname", "-f", NULL});
    execute_program((char *[]){"/usr/bin/realpath", ".", NULL});
    return 0;
}
