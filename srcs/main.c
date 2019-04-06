#include "lexer.h"
#include "ast.h"



char	**create_argv(t_tklst *tklst, int len)
{
	char	**res;
	int		i;

	if (!(res = malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	i = 0;
	res[len] = NULL;
	while (i < len)
	{
		res[i] = ft_strdup(tklst->token->content);//strndup
		tklst = tklst->next;
		i++;
	}
	return (res);
}

char	**get_argv(t_tklst *tklst)
{
	int		len;
	t_tklst	*probe;

	if (!(probe = tklst))
		return (NULL);
	len = 0;
	while(probe && probe->token->type == TK_LITERAL)
	{
		len++;
		probe = probe->next;
	}
	if (len < 1)
		return (NULL);
	return (create_argv(tklst, len));
}

static void	redirect(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) != -1)
			close(old_fd);
		else
			printf("error with dup2\n");
	}
}

static int	run(char * const* argv, int in, int out)
{
	redirect(in, STDIN_FILENO);
	redirect(out, STDOUT_FILENO);
	return (execvp(argv[0], (char* const*)argv));//should be parsing func here
}

int 		spawn_proc (int in, int out, char **argv)
{
	pid_t pid;

	if (!argv || !*argv)
		return (-1);

	return (1);// ? parent process
}

int	fork_pipes(int n, t_tklst *tklst)
{
	int i;
	int in;
	char **argv;
	pid_t	pid;
	int		stat;
	int fd[2];

	in = STDIN_FILENO;
	i = 0;
	if (!(argv = get_argv(tklst)))//should be simple commands
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
		while (tklst && tklst->token->type == TK_LITERAL)
			tklst = tklst->next;
		while (tklst && tklst->token->type != TK_LITERAL) // opti ?
			tklst = tklst->next;
		if (!(argv = get_argv(tklst)))//should be simple commands
			return (0);
	}
	return (run((char* const*)argv, in, STDOUT_FILENO));
}

static int	is_simple_cmd_token(t_tklst *probe)
{
	if (!probe)
		return (0);
	if (probe->token->type == TK_LITERAL
			|| probe->token->type == TK_SQ_STR
			|| probe->token->type == TK_DQ_STR
			|| probe->token->type == TK_REDIRECTION)
		return (1);
	else
		return (0);
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

int	main(void)
{
	t_tklst *tklst;;

	tklst = NULL;
	add_token_to_tklst(create_token("ls", 2, TK_LITERAL), &tklst);
	add_token_to_tklst(create_token("|", 1, TK_PIPE), &tklst);
	add_token_to_tklst(create_token("wc", 2, TK_LITERAL), &tklst);
	printf("--- OUTPUT ---\n");
	parse_pipeline(tklst);
	return (0);
}
