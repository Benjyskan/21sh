#include "lexer.h"
#include "ast.h"

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
	token_head->type = TK_WORD;
	return (0);
}

t_bool	parse_quotes(t_token *token_head)
{
	while (token_head && token_head->type < TK_PIPE)
	{
		if (token_head->type == TK_SQ_STR || token_head->type == TK_DQ_STR)
			return (expand_quotes(token_head));
		token_head = token_head->next;
	}
	return (0);
}
