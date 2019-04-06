#include "lexer.h"
#include "ast.h"

static int	run(char * const* argv, int in, int out)
{
	redirect(in, STDIN_FILENO);
	redirect(out, STDOUT_FILENO);
	return (execvp(argv[0], (char* const*)argv));//should be parsing func here
}

static t_tklst *get_next_simple_command(t_tklst *tklst)
{
	while (tklst && tklst->token->type == TK_LITERAL)
		tklst = tklst->next;
	while (tklst && tklst->token->type != TK_LITERAL) // opti ?
		tklst = tklst->next;
	return (tklst);
}

static int	fork_pipes(int n, t_tklst *tklst)
{
	int i;
	int in;
	char **argv;
	pid_t	pid;
	int fd[2];

	in = STDIN_FILENO;
	i = 0;
	if (!(argv = get_argv_from_tokens(tklst)))//should be simple commands
		return (0);
	while (i < n - 1)
	{
		if (pipe(fd)) //check_error
			printf("pipe error\n");
		if ((pid = fork()) == -1)
			printf("fork error\n");//TODO
		else if (pid == 0)
		{
			close(fd[0]);//check return value
			run((char* const*)argv, in, fd[1]); // check return value ?
		}
		close(fd[1]);
		close(in);
		in = fd[0];
		i++;
		tklst = get_next_simple_command(tklst);
		if (!(argv = get_argv_from_tokens(tklst)))//should be simple commands
			return (0);
	}
	return (run((char* const*)argv, in, STDOUT_FILENO));
}

t_pipelst	*parse_pipeline(t_tklst *tklst)
{
	int	len;
	t_tklst *probe;

	if (!tklst)
		return (NULL);
	len = 1;
	probe = tklst;
	while (probe)
	{
		if (!is_simple_cmd_token(probe))
		{
			printf("ERROR: bad '|' syntax\n");
			return (NULL);
		}
		while (is_simple_cmd_token(probe)) //continue on simple_cmd tokens
			probe = probe->next;
		if (probe && probe->next && (probe->token->type == TK_PIPE)) // is a pipe and not empty after
		{
			probe = probe->next;
			len++;
		}
	}
	printf("RES: %d\n", fork_pipes(len, tklst));
	return (NULL);
}
