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
			close(old_fd);
		else
			dprintf(2, "error with dup2\n");
	}
}

static int		check_fd_prev(t_token *prev)
{
	int	i;
	if (!prev)
		return (1);
	if (prev->type == TK_WORD)
	{
		i = 0;
		while (prev->content[i])
		{
			if (!ft_isalnum(prev->content[i]))
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
	int		old_fd;
	t_token	*next;
	int		new_fd;

	if (redir && ft_strncmp(redir->content, ">", 2) == 0) // only >
	{
		old_fd = check_fd_prev(prev);
		next = redir->next;
		while (next->type == TK_EAT) // need functions that does this
			next = next->next;
		if ((new_fd = open(next->content, O_WRONLY | O_CREAT | O_TRUNC), 0640) < 0)
		{
			dprintf(2, "error openening file\n");
			return (0);
		}
		redirect(new_fd, old_fd);
		redir->type = TK_EAT;
		next->type = TK_EAT; // if I dont check is_argv i will segfault on deference
		return (1);
	}
	else
		return (0);
}

static	t_bool	execute_tokens(t_token *token_head)
{
	(void)token_head;
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
