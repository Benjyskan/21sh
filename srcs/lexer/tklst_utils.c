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
	if (is_delimiter(cmdline[size]) || cmdline[size] == 0)
		new_token->is_delimited = 1;
	else
		new_token->is_delimited = 0;
	new_token->discarded = 0;
	print_token(new_token);
	return (new_token);
}

t_tklst	*create_tklst_node(t_token *token)
{
	t_tklst	*tklst_node;

	if (!(tklst_node = malloc(sizeof(*tklst_node))))
		return (NULL);
	tklst_node->token = token;
	tklst_node->next = NULL;
	return (tklst_node);
}

t_bool	add_token_to_tklst(t_token *token, t_tklst **tklst_head)
{
	t_tklst	*probe;

	if (*tklst_head == NULL)
	{
		if (!(*tklst_head = create_tklst_node(token)))
			return (0);
		printf("in add_to_tklst: {%s}\n", (*tklst_head)->token->content);
		return (1);
	}
	probe = *tklst_head;
	while (probe->next)
		probe = probe->next;
	if (!(probe->next = create_tklst_node(token)))
		return (0);
	return (1);
}
