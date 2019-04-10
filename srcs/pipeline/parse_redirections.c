#include "ast.h"
#include "lexer.h"

t_bool	is_simple_cmd_token(t_token *probe) //static ?
{
	if (!probe)
		return (0);
	if (probe->type < TK_PIPE)
		return (1);
	else
		return (0);
}

void	redirect(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) != -1)
			close(old_fd); //check close return ?
		else
			dprintf(2, "error with dup2: old_fd: %d, new_fd: %d\n", old_fd, new_fd);
	}
}

int		check_fd_prev(t_token *prev)
{
	int	i;
	if (!prev)
		return (1);
	if (prev->type == TK_WORD)
	{
		i = 0;
		while (prev->content[i])
		{
			if (!ft_isdigit(prev->content[i]))
				dprintf(2, "NOT ALNUM\n");
				return (1);
			i++;
		}
		prev->type = TK_EAT;
		return (ft_atoi(prev->content));
	}
	else
		return (1);
}

t_bool	apply_redirections(t_token *redir, t_token *prev) //static ?
{
	if (!redir)
		return (0);
	if (ft_strncmp(redir->content, ">", 2) == 0) // only >
		redir_great(redir, prev);
	else if (ft_strncmp(redir->content, ">>", 3) == 0)
		redir_dgreat(redir, prev);
	else if (ft_strncmp(redir->content, "<", 2) == 0)
		redir_less(redir, prev);
	else if (ft_strncmp(redir->content, "<<", 3) == 0)
		redir_dless(redir, prev);
	else
		return (0);
	return (1);
}

t_bool	parse_redirections(t_token *token_head)
{
	t_token	*current;
	t_token	*prev;

	current = token_head;
	if (!current)
		return (0);
	if (current->type == TK_REDIRECTION)
		if (apply_redirections(current, NULL) == 0)
			return (0);
	prev = current;
	current = current->next;
	while (is_simple_cmd_token(current))
	{
		if (current->type == TK_REDIRECTION)
			if (apply_redirections(current, prev) == 0)
				return (0);
		prev = current;
		current = current->next;
	}
	return (execute_tokens(token_head));
}
