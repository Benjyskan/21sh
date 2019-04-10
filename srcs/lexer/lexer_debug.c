#include "tosh.h"

void	print_token(t_token *token)//debug
{
	printf("TOKEN{\n\tcontent: {%s}\n\tsize: %lu\n\ttype: %d\n}\n", 
			token->content,
			token->size,
			token->type);
}

void	print_token_list(t_token *token_head)//debug
{
	t_token	*probe;

	ft_putendl("--Printing token list--");
	probe = token_head;
	while (probe)
	{
		//printf("probe->next add: %p\n", probe);
		print_token(probe);
		probe = probe->next;
	}
}
