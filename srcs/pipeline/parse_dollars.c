#include "lexer.h"
#include "ast.h"

static t_bool	expand_dollars(t_token *token_head)
{
	(void)token_head;
	return (0);
}

t_bool			parse_dollars(t_token *token_head)
{
	t_bool	res;

	res = 0;
	while (token_head && token_head->type < TK_PIPE)
	{
		if (token_head->type == TK_WORD || token_head->type == TK_DQ_STR)
		{
			res = 1;
			expand_dollars(token_head);
		}
		token_head = token_head->next;
	}
	return (res);
}
