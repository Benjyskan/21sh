#include "tosh.h"
#include "lexer.h"

t_token	*create_token(char *cmdline, size_t size, t_token_type type)
{
	t_token	*new_token;

	if (!(new_token = malloc(sizeof(t_token))))
	{
		ft_putendl_fd("malloc failed in create_token", 2);
		return (NULL);
	}
	new_token->size = size;
	new_token->type = type;
	if (!(new_token->content = ft_strndup(cmdline, size)))
	{
		ft_memdel((void*)&new_token);//TODO check me
		ft_putendl_fd("malloc failed in create_token", 2);
		return (NULL);
	}
	new_token->next = NULL;
	return (new_token);
}

void	add_token_to_list(t_token *token, t_token **token_head)
{
	t_token	*probe;

	if (*token_head == NULL)
	{
		*token_head = token;
		return ;
	}
	probe = *token_head;
	while (probe->next)
		probe = probe->next;
	probe->next = token;
	return ;
}
