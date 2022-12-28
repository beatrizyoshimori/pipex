#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"

int main(int argc, char *argv[])
{
    int fd1[2];
    // int fd2[2];
    int pid;
    // char str1[4] = "oi, ";
    // char str2[9] = "tudo bem?";
    // char str_conc[20];
    
    if (pipe(fd1) == -1)
        return (1);
    // if (pipe(fd2) == -1)
    //     return (1);
    pid = fork();
    if (pid < 0)
        return (1);
    // else if (pid > 0)
    // {
    //     close(fd1[0]);
    //     write(fd1[1], str1, 4);
    //     close(fd1[1]);
    //     wait(NULL);
    //     close(fd2[1]);
    //     printf("antes do read: %s\n", str_conc);
    //     read(fd2[0], str_conc, 20);
    //     printf("%s\n", str_conc);
    //     close(fd2[0]);
    // }
    // else
    // {
    //     close(fd1[1]);
    //     read(fd1[0], str_conc, 20);
    //     int i = 0;
    //     int j = strlen(str_conc);
    //     while (i < strlen(str2))
    //         str_conc[j++] = str2[i++];
    //     str_conc[j] = '\0';
    //     close(fd1[0]);
    //     close(fd2[0]);
    //     write(fd2[1], str_conc, strlen(str_conc) + 1);
    //     close(fd2[1]);
    //     printf("child: %s\n", str_conc);
    //     exit(0);
    // }

    char **str = ft_split(argv[1], ' ');
    if (pid == 0)
    {
        //char *str[] = {"ls", "-l", NULL};
        dup2(fd1[1], 1);
        close(fd1[0]);
        close(fd1[1]);
        execvp("ls", str);
    }

    int pid2 = fork();
    if (pid2 < 0)
        return (1);
    char **str2 = ft_split(argv[2], ' ');
    if (pid2 == 0)
    {
        //char *str2[] = {"grep", "txt", NULL};
        dup2(fd1[0], 0);
        close(fd1[0]);
        close(fd1[1]);
        execvp("grep", str2);
    }
    close(fd1[0]);
    close(fd1[1]);
    waitpid(pid, NULL, 0);
    waitpid(pid2, NULL, 0);
}