#include "ast.h"
#include "lexer.h"

t_bool		redir_less(t_token *redir, t_token *prev)
{
	int		old_fd;
	t_token	*next;
	int		new_fd;

	if ((old_fd = check_fd_prev(prev)) < 0)
		old_fd = 0;
	next = redir->next;
	while (next->type == TK_EAT)
		next = next->next;
	if ((new_fd = open(next->content, O_RDONLY)) < 0)
	{
		dprintf(2, "error opening file\n");
		return (0);
	}
	redirect(new_fd, old_fd);
	redir->type = TK_EAT;
	next->type = TK_EAT;
	return (1);
}
