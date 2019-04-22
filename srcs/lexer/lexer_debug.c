#include "tosh.h"

void	print_token(t_token *token)//debug
{
	ft_endl_tty("_TOKEN_");
	ft_putstr_tty("content: {");
	ft_putstr_tty(token->content);
	ft_endl_tty("}");
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
