#include "lexer.h"
#include "ast.h"

static t_bool	expand_dollars(t_token *token_head)
{
	return (0);
}

t_bool			parse_dollars(t_token *token_head)
{
	while (token_head && token_head->type < TK_PIPE)
	{
		if (token_head->type == TK_WORD || token_head->type == TK_DQ_STR)
			return (expand_dollars(token_head));
		token_head = token_head->next;
	}
	return (0);
}
