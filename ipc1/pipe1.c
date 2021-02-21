#include "apue.h"

int
main(void)
{
	int		n;
	int		fd[2];
	pid_t	pid;
	char	line[MAXLINE];

	if (pipe(fd) < 0)
		err_sys("pipe error");
	if ((pid = fork()) < 0) {
		err_sys("fork error");
	} else if (pid > 0) {		/* parent */
        printf("fd[0]:%d, fd[1]:%d.\n", fd[0], fd[1]);
		/* close(fd[0]); */
		write(fd[1], "hello world from parent.\n", 25);
        /* wait child to write the msg to pipe */
        sleep(1);
        n = read(fd[0], line, MAXLINE);
        write(STDOUT_FILENO, line, n);
	} else {					/* child */

        printf("fd[0]:%d, fd[1]:%d.\n", fd[0], fd[1]);
		/* close(fd[1]); */
		n = read(fd[0], line, MAXLINE);
		write(STDOUT_FILENO, line, n);
        write(fd[1], "hello world from child.\n", 24);
	}
	exit(0);
}
