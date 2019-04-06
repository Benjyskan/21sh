#include "ast.h"
#include "lexer.h"

int	is_simple_cmd_token(t_tklst *probe)
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

/*
**	Apply redirections in the simple_command with dup2()
*/

static int		apply_redirections(t_tklst **begin)
{
	(void)begin;
	return (1);
}

/*
**	Applies basic redirections, applies useful redirections 
**	by calling apply_redirections then creates an argv
**	list that's given out to parse_argv
*/

int		parse_redir(t_tklst *begin, int in, int out) 
{
	char	**argv;

	redirect(in, STDIN_FILENO); // might pass in and out to other function instead of redirecting right away ?
	redirect(out, STDOUT_FILENO);
	apply_redirections(&begin);
	if (!(argv = get_argv_from_tokens(begin)))
	{
		printf("error\n");
		return (0);
	}
	return (execvp(argv[0], (char* const*)argv)); // should be parse_argv
}

void	redirect(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) != -1)
			close(old_fd);
		else
			printf("error with dup2\n");
	}
}
