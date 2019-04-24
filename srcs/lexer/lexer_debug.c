#include "tosh.h"

void	print_token(t_token *token)//debug
{
	ft_dprintf(g_dev_tty, "_TOKEN_ type:%d {%s}", token->type, token->content);
	print_line();
}

void	print_token_list(t_token *token_head)//debug
{
	t_token	*probe;

	ft_endl_tty("--Printing token list--");
	probe = token_head;
	while (probe)
	{
		//printf("probe->next add: %p\n", probe);
		print_token(probe);
		probe = probe->next;
	}
}
