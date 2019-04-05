#include <unistd.h>

struct command
{
	const char **argv;
};

int spawn_proc (int in, int out, struct command *cmd)
{
	pid_t pid;

	if ((pid = fork()) == 0)
	{
		if (in != 0)
		{
			dup2(in, 0);
			close(in);
		}
		if (out != 1)
		{
			dup2(out, 1);
			close(out);
		}
		return (execvp(cmd->argv[0], (char* const*)cmd->argv));
	}
	return (pid);
}

int	fork_pipes(int n, struct command *cmd)
{
	int i;
	int in;
	int fd[2];

	in = 0;
	i = 0;
	while (i < n - 1)
	{
		pipe(fd);

		spawn_proc(in, fd[1], cmd + i);
		close(fd[1]);
		in = fd[0];
		i++;
	}

	if (in != 0)
		dup2(in, 0);
	return (parse_simple_cmd(cmd));
}

int	main(void)
{
	const char *ls[] = { "ls", 0};
	const char *sort[] = { "sort", "-r", 0};
	const char *uniq[] = { "uniq", 0};

	struct command cmd[] = { {ls}, {sort}, {uniq}};

	return (fork_pipes(3, cmd));
}
