#include "tosh.h"

int		my_pipe(char *input)
{
	int		fd[2];
	pid_t	pid;
	char	buf[100];
	char	output[100];
	int		i;

	ft_putendl("$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$");
	if (pipe(fd) == -1)
	{
		ft_putendl("pipe failed");
		return (0);
	}
	//printf("fd[0]=%d, fd[1]=%d\n", fd[0], fd[1]);
	if ((pid  = fork()) < 0)
	{
		ft_putendl("fork failed");
		return (0);
	}
	else if (pid > 0)//PARENT
	{
		printf("fd[0]: %d, fd[1]: %d\n", fd[0], fd[1]);
		if (close(fd[0]) == -1)
			ft_putendl("close fd[0] error");
		(void)input;
		printf("input_len: %zu\n", ft_strlen(input));
		write(fd[1], input, ft_strlen(input) - 1);
		write(fd[1], "X", 1);
		if (close(fd[1]) == -1)
			ft_putendl("close fd[1] error)");
		wait(0);
	}
	else//CHILD
	{
		printf("fd[0]: %d, fd[1]: %d\n", fd[0], fd[1]);
		if (close(fd[1]) == -1)
			ft_putendl("close fd[1] error");
		read(fd[0], buf, 100);
		if (close(fd[0]) == -1)
			ft_putendl("close fd[0] error");
		i = -1;
		while (buf[++i])
			output[i] = ft_toupper(buf[i]);
		output[i] = 0;
		printf("%s\n", output);
		exit (1);
	}
	return (0);
}
