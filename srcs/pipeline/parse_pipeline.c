#include "lexer.h"
#include "ast.h"

/*
**	Returns the next simple_command (the one after the next pipe), if there
**	is one.
**	Should not return NULL because it is called n - 1 times
*/

static t_token *get_next_simple_command(t_token *begin)
{
	while (is_simple_cmd_token(begin))
		begin = begin->next;
	if (begin && begin->type == TK_PIPE)
		return (begin->next);
	else
	{
		printf("Error ???\n");
		return (begin); //error ?
	}
}

/*
**	Manages all pipes and fds, while handing the simple command to parse_redir
**	for redirection parsing and execution. Note that i < n - 1, because piping \
**	the last command is never needed.
*/

static int	fork_pipes(int num_simple_commands, t_token *begin)
{
	int i; // num_simple_commands - 1 can decrement
	int in;
	pid_t	pid;
	int fd[2];

	in = STDIN_FILENO;
	i = 0;
	while (i < num_simple_commands - 1)
	{
		if (pipe(fd))
		{
			printf("pipe error\n");
			return (0);
		}
		if ((pid = fork()) == -1)
			printf("fork error\n");//TODO
		else if (pid == 0)
		{
			close(fd[0]);//check return value
			return (parse_expands(begin, in, fd[1]));
		}
		else if (pid > 0)
		{
			close(fd[1]);
			close(in);
			in = fd[0];
			i++;
			begin = get_next_simple_command(begin);
		}
	}
	return (parse_expands(begin, in, STDOUT_FILENO));
}

/*
** First counts the number of pipes and checks for correct pipe syntax
** then hands the token list to fork_pipes to handle pipes.
*/

int			parse_pipeline(t_token *token) // no need for t_pipelst ?
{
	int	num_simple_commands;
	t_token *probe;

	if (!token)
		return (0);
	num_simple_commands = 1;
	probe = token;
	while (probe)
	{
		while (probe && is_simple_cmd_token(probe)) //continue on simple_cmd tokens
			probe = probe->next;
		if (probe && probe->next && (probe->type == TK_PIPE)) // is a pipe and not empty after
		{
			probe = probe->next;
			num_simple_commands++;
		}
	}
	return (fork_pipes(num_simple_commands, token));
}