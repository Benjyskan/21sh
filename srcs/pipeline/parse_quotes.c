#include "lexer.h"
#include "ast.h"

/*
**	Does not change token_head->type to TK_WORD because we need to know the
**	orginal type for redirections.
*/

static t_bool	expand_quotes(t_token *token_head)
{
	char	*old_content;

	if (*token_head->content == '\'' || *token_head->content == '"')
	{
		old_content = token_head->content;
		if (!(token_head->content = ft_strndup((const char*)&(*(token_head->content + 1)), ft_strlen(token_head->content) - 2)))
			ERROR_MEM;
		free(old_content);
		return (1);
	}
	return (0);
}

t_bool	parse_quotes(t_token *token_head)
{
	t_bool	res;

	res = 0;
	while (token_head && token_head->type < TK_PIPE)
	{
		if (token_head->type == TK_SQ_STR || token_head->type == TK_DQ_STR)
		{
			res = 1;
			expand_quotes(token_head);
		}
		token_head = token_head->next;
	}
	return (res);
}
