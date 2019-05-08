#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd[2];

	pipe(fd);
	dup2(fd[1], STDIN_FILENO);
	dup2(fd[0], STDOUT_FILENO);
	close(fd[1]);
	close(fd[0]);
	write(STDOUT_FILENO, "salut", 5);
	return (1);
}
