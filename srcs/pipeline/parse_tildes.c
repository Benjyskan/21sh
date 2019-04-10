#include "lexer.h"
#include "ast.h"

static t_bool	tild_expand(t_token *token_head)
{
	char	*old_content;

	if (*token_head->content == '~')
	{
		old_content = token_head->content;
		if (!(token_head->content = ft_strndup("TILD", 4))) // look for environement functions to get value from key "HOME" and protect the function
			ERROR_MEM;
		free(old_content);
		return (1);
	}
	return (0);
}

t_bool	parse_tildes(t_token *token_head)
{
	while (token_head && token_head->type < TK_PIPE)
	{
		if (token_head->type == TK_WORD || token_head->type == TK_DQ_STR)
			return (tild_expand(token_head));
		token_head = token_head->next;
	}
	return (0);
}
