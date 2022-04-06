#include <minishell.h>
#include <string.h>

int main()
{
	char	*line_read;
	int		pipe_fds[2];
	int		pid;
	char	buffer[100];

	pipe(pipe_fds);
	pid = fork();
	if (pid == 0)
	{
		line_read = readline("> ");
		printf("line read: >|%s|<  size: %li\n", line_read, strlen(line_read));
		write(pipe_fds[1], line_read, strlen(line_read));
		printf("fez o write\n");
		exit(0);
	}
	else
		wait(NULL);
	close(pipe_fds[1]);
	read(pipe_fds[0], buffer, 99);
	printf("fez o read\n");
	printf("resultado: >%s<\n", buffer);
	return 0;
}