 #include <sys/types.h>
 #include <unistd.h>
 #include <stdio.h>
 #include <stdlib.h>
#include <fcntl.h>

int main(void)
{
	int		pipes[2];
	char	buf[1024];
	pid_t	pid;
	
	pipe(pipes); // Create the pipes
	pid = fork();

	if (pid == 0)
	{
		dup2(pipes[1],1); // Set the pipe up to standard output
		printf ("%s\n", "Hello World!");
	}
	int n = read(pipes[0], buf, 1024);
	close(pipes[1]);
	close(pipes[0]);
	write(1, buf, n);
}