#include "ast.h"
#include <errno.h>
#include "lexer.h"

/*
**	Checks to see if token is a redirection, simple quote, double quote,
**	string literal, or whitespace (TK_EAT)
*/

t_bool	is_simple_cmd_token(t_token *probe)
{
	if (!probe)
		return (0);
	if (is_argv_token(probe) || probe->type == TK_REDIRECTION
			|| probe->type == TK_EAT)
		return (1);
	else
		return (0);
}

/*
**	Checks if previous token before a redirection needs to be interpreted as a
**	or as a regular file file descriptor
*/

static t_bool		check_fd_prev(t_tklst *prev)
{
	int i;

	if (!prev)
		return (1);
	if (prev->token->type == TK_LITERAL)
	{
		i = 0;
		while (prev->token->content[i])
		{
			if (!ft_isalnum(prev->token->content[i]))
			{
				prev->token->discarded = 1;
				return (1);
			}
			i++;
		}
		return (ft_atoi(prev->token->content));
	}
	else
		return (1);
}

/*
**	Applies redirections in the simple_command with dup2()
*/

static int		apply_redirections(t_tklst *redir, t_tklst *prev) // for '>' only
{
	int		old_fd;
	t_tklst *next;
	int		new_fd;

	if (redir && ft_strncmp(redir->token->content, ">", 2) == 0)
	{
		new_fd = check_fd_prev(prev);
		next = redir->next;
 		while (next && (next->token->type == TK_EAT))
			next = next->next;
		if (!next || (next->token->type != TK_SQ_STR
				&& next->token->type != TK_LITERAL
				&& next->token->type != TK_DQ_STR))
		{
			printf("Bad syntax error near REDIR token\n");
			return (0);
		}
		if ((old_fd = open(next->token->content, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0640)) < 0) // should be func like "parse" quotes and expand name
		{
			// close previous
			printf("errno: {%d}\n", errno);
			perror(strerror(errno));
			printf("error opening file\n");
			return (0);
		}
		redirect(old_fd, new_fd);
		redir->token->discarded = 1;
		next->token->discarded = 0;
		if (write(1, "c'est pas moi\n", 10) < 0)
			dprintf(2, "error in write\n");
		return (1);
	}
	printf("Not '>' token\n");
	return (0);
}

/*
**	Applies first basic redirections, applies useful redirections 
**	by calling apply_redirections then creates an argv
**	list that's given out to parse_argv
*/

int		parse_redir(t_tklst *begin, int in, int out) 
{
	char	**argv;
	t_tklst	*current;
	t_tklst	*prev;

	redirect(in, STDIN_FILENO); // might pass in and out to other function instead of redirecting right away ?
	redirect(out, STDOUT_FILENO);
	current = begin;
	if (!current)
		return (0);
	if ((current->token->type == TK_REDIRECTION) && ft_strncmp(">", current->token->content, 2) == 0)
		if (apply_redirections(current, NULL) == 0)
			return (0);
	prev = current;
	printf("CURR: %s\n", current->token->content);
	current = current->next;
	while (current)
	{
		printf("CURR: %s\n", current->token->content);
		if ((current->token->type == TK_REDIRECTION) && ft_strncmp(">", current->token->content, 2) == 0)
			if (apply_redirections(current, prev) == 0)
				return (0);
		prev = current;
		current = current->next;
	}
	if (current && current->token->type == TK_REDIRECTION)
	{
		printf("Redirecton parsing error\n");
		return (0);
	}
	if (!(argv = get_argv_from_tokens(begin)))
	{
		printf("error argv is null\n");
		return (0);
	}
	int i = 0;
	while (argv[i])
	{
		dprintf(2, "argv[%d]: %s\n", i, argv[i]);
		i++;
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
