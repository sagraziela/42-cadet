/bin/ls
1.txt
a.out
microshell
microshell.c
model
out.res
test.sh
teste

/bin/cat microshell.c
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>

// https://github.com/TalhaAksoy/microshellExam/blob/main/main.c
// https://github.com/shackbei/microshell-42/blob/main/microshell.c

/*not needed in exam, but necessary if you want to use this tester:
https://github.com/Glagan/42-exam-rank-04/blob/master/microshell/test.sh*/
#ifdef TEST_SH
# define TEST		1
#else
# define TEST		0
#endif

void    ft_putstr_fd2(char *str, char *arg)
{
    int i;

    i = 0;
    while (str[i])
    {
        write(2, &str[i], 1);
        i++;
    }
    if (arg)
    {
        i = 0;
        while (arg[i])
        {
            write(2, &arg[i], 1);
            i++;
        }
    }
    write(2, "\n", 1);
}

void    ft_execute(char *argv[], int i, int tmp_fd, char *env[])
{
    argv[i] = NULL; //overwrite the ";" or "|" to NULL to use array as input to execve()
    dup2(tmp_fd, STDIN_FILENO); //create a child so we dont impact the parent process
    close(tmp_fd);
    execve(argv[0], argv, env);
    ft_putstr_fd2("error: cannot execute ", argv[0]);
    exit(1);
}

int main(int argc, char *argv[], char *env[])
{
    int fd[2];
    int tmp_fd;
    int i;

    i = 0;
    tmp_fd = dup(STDIN_FILENO);
    (void)argc;
    while (argv[i] && argv[i + 1])
    {
        argv = &argv[i + 1]; //the new argv start after the ; or |
        i = 0;
        // now we count until we have all the info to exec the next child:
        while (argv[i] && strcmp(argv[i], ";") && strcmp(argv[i], "|"))
            i++;
        if (strcmp(argv[0], "cd") == 0)
        {
            //printf("Caiu no CD\n");
            if (i != 2)
                ft_putstr_fd2("error: cd: bad arguments", NULL);
            else if (chdir(argv[1]) != 0)
                ft_putstr_fd2("error: cd: cannot change directory to ", argv[1]);
        }
        else if (i != 0 && (argv[i] == NULL || strcmp(argv[i], ";") == 0)) //exec in stdout
        {
            //printf("CAIU NO PONTO-VIRGULA\n");
            if (fork() == 0)
                ft_execute(argv, i, tmp_fd, env);
            else
            {
                close(tmp_fd);
                while (waitpid(-1, NULL, WUNTRACED) != -1)
                    ;
                tmp_fd = dup(STDIN_FILENO);
            }
        }
        else if (i != 0 && strcmp(argv[i], "|") == 0)
        {
            //printf("CAIU NO PIPE\n");
            pipe(fd);
            if (fork() == 0)
            {
                dup2(fd[1], STDOUT_FILENO);
                close(fd[0]);
                close(fd[1]);
                ft_execute(argv, i, tmp_fd, env);
            }
            else
            {
                close(fd[1]);
                close(tmp_fd);
                tmp_fd = fd[0];
            }
        }
    }
    close(tmp_fd);
    return (0);
}

// gcc ./microshell.c -Wall -Wextra -Werror -g3
/bin/ls microshell.c
microshell.c

/bin/ls salut

;

; ;

; ; /bin/echo OK
OK

; ; /bin/echo OK ;
OK

; ; /bin/echo OK ; ;
OK

; ; /bin/echo OK ; ; ; /bin/echo OK
OK
OK

/bin/ls | /usr/bin/grep microshell
microshell
microshell.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro
microshell
microshell.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro
microshell
microshell.c

/bin/ls | /usr/bin/grep microshell | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep micro | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell | /usr/bin/grep shell
microshell
microshell.c

/bin/ls ewqew | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo
dernier


/bin/ls | /usr/bin/grep micro | /bin/cat -n ; /bin/echo dernier ; /bin/echo ftest ;
     1	microshell
     2	microshell.c
dernier
ftest

/bin/echo ftest ; /bin/echo ftewerwerwerst ; /bin/echo werwerwer ; /bin/echo qweqweqweqew ; /bin/echo qwewqeqrtregrfyukui ;
ftest
ftewerwerwerst
werwerwer
qweqweqweqew
qwewqeqrtregrfyukui

/bin/ls ftest ; /bin/ls ; /bin/ls werwer ; /bin/ls microshell.c ; /bin/ls subject.fr.txt ;
1.txt
a.out
leaks.res
microshell
microshell.c
model
out.res
test.sh
teste
microshell.c

/bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ; /bin/ls | /usr/bin/grep micro ;
microshell
microshell.c
microshell
microshell.c
microshell
microshell.c
microshell
microshell.c

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b ; /bin/cat subject.fr.txt ;

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep w ; /bin/cat subject.fr.txt ;

/bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep w ; /bin/cat subject.fr.txt

/bin/cat subject.fr.txt ; /bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat subject.fr.txt

; /bin/cat subject.fr.txt ; /bin/cat subject.fr.txt | /usr/bin/grep a | /usr/bin/grep b | /usr/bin/grep z ; /bin/cat subject.fr.txt

blah | /bin/echo OK
OK

blah | /bin/echo OK ;
OK

