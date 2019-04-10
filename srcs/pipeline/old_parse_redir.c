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
		old_fd = check_fd_prev(prev);
		next = redir->next;
 		while (next && (next->type == TK_EAT))
			next = next->next;
		if (!is_argv_token(next)) // should not have to check
		{
			dprintf(2, "Bad syntax error near REDIR token\n"); 
			return (0);
		}
		if ((new_fd = open(next->content, O_WRONLY | O_CREAT | O_TRUNC | O_APPEND, 0640)) < 0) // should be func like "parse" quotes and expand name
		{
			// close previous
			dprintf(2, "errno: {%d}\n", errno);
			perror(strerror(errno));
			dprintf(2, "error opening file\n");
			return (0);
		}
		dprintf(2, "REDIR: NAME: %s, OLD: %d, NEW: %d\n", redir->content, old_fd, new_fd);
		redirect(new_fd, old_fd);
		redir->type = TK_EAT;
		next->type = TK_EAT;
		return (1);
	}
	dprintf(2, "Not '>' token\n");
	return (0);
}

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

/*
**	Applies first basic redirections, applies useful redirections 
**	by calling apply_redirections then creates an argv
**	list that's given out to parse_argv
*/

int		parse_redir(t_token *begin, int in, int out) 
{
	t_token	**token_argv;
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
	while (current && current->type != TK_PIPE)
	{
//		dprintf(2, "CURRENT: %s\n", current->content);
		if ((current->type == TK_REDIRECTION) && ft_strncmp(">", current->content, 2) == 0) //only '>'
		{
			dprintf(2, "APPLYING REDIR, %s\n", current->content);
			if (apply_redirections(current, prev) == 0)
				return (0);
		}
		prev = current;
		current = current->next;
	}
	if (current && current->type == TK_REDIRECTION) // ???
	{
		dprintf(2, "Redirecton parsing error\n");
		return (0);
	}
	if (!(token_argv = (t_token**)get_argv_from_tokens(begin)))
	{
		dprintf(2, "error argv is null\n");
		return (0);
	}
	print_token_tab(token_argv);
	return (parse_expands(token_argv));// should be parse_argv
}


