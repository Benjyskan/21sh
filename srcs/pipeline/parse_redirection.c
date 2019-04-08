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

static t_bool		check_fd_prev(t_token *prev)
{
	int i;

	if (!prev)
		return (1);
	if (prev->type == TK_WORD)
	{
		i = 0;
		while (prev->content[i])
		{
			if (!ft_isalnum(prev->content[i]))
			{
				prev->type = TK_EAT;
				return (1);
			}
			i++;
		}
		return (ft_atoi(prev->content));
	}
	else
		return (1);
}

/*
**	Applies redirections in the simple_command with dup2()
*/

static int		apply_redirections(t_token *redir, t_token *prev) // for '>' only
{
	int		old_fd;
	t_token *next;
	int		new_fd;

	if (redir && ft_strncmp(redir->content, ">", 2) == 0) // only '>'
	{
		new_fd = check_fd_prev(prev);
		next = redir->next;
 		while (next && (next->type == TK_EAT))
			next = next->next;
		if (!is_argv_token(next)) // should not have to check
		{
			dprintf(2, "Bad syntax error near REDIR token\n"); 
			return (0);
		}
		if ((old_fd = open(next->content, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0640)) < 0) // should be func like "parse" quotes and expand name
		{
			// close previous
			dprintf(2, "errno: {%d}\n", errno);
			perror(strerror(errno));
			dprintf(2, "error opening file\n");
			return (0);
		}
		redirect(old_fd, new_fd);
		redir->type = TK_EAT;
		next->type = TK_EAT;
		if (write(1, "c'est pas moi\n", 10) < 0)
			dprintf(2, "error in write\n");
		return (1);
	}
	dprintf(2, "Not '>' token\n");
	return (0);
}

/*
**	Applies first basic redirections, applies useful redirections 
**	by calling apply_redirections then creates an argv
**	list that's given out to parse_argv
*/

void	print_token_tab(t_token **argv)
{
	int i;
	t_token *tmp;

	if (!argv || !*argv)
		return ;
	i = 0;
	while (argv[i])
	{
		tmp = argv[i];
		dprintf(2, "ARGV[%d]:\t", i);
		while (tmp && tmp->type != TK_EAT && tmp->type != TK_PIPE)
		{
			dprintf(2, "%s\t", tmp->content);
			tmp = tmp->next;
		}
		dprintf(2, "\n");
		i++;
	}
}

int		parse_redir(t_token *begin, int in, int out) 
{
	t_token	**argv;
	t_token	*current;
	t_token	*prev;

	dprintf(2, "HERE: %s, IN: %d, OUT: %d\n", begin->content, in, out);
	redirect(in, STDIN_FILENO); // might pass in and out to other function instead of redirecting right away ?
	redirect(out, STDOUT_FILENO);
	current = begin;
	if (!current)
		return (0);
	if ((current->type == TK_REDIRECTION) && ft_strncmp(">", current->content, 2) == 0)
		if (apply_redirections(current, NULL) == 0)
			return (0);
	prev = current;
	current = current->next;
	while (current)
	{
		if ((current->type == TK_REDIRECTION) && ft_strncmp(">", current->content, 2) == 0) //only '>'
			if (apply_redirections(current, prev) == 0)
				return (0);
		prev = current;
		current = current->next;
	}
	if (current && current->type == TK_REDIRECTION)
	{
		dprintf(2, "Redirecton parsing error\n");
		return (0);
	}
	if (!(argv = (t_token**)get_argv_from_tokens(begin)))
	{
		dprintf(2, "error argv is null\n");
		return (0);
	}
	print_token_tab(argv);
	return (parse_expands(argv));// should be parse_argv
}

void	redirect(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) != -1)
			close(old_fd);
		else
			dprintf(2, "error with dup2\n");
	}
}
