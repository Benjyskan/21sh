#include "ast.h"
#include "lexer.h"

t_bool	is_quote_token(t_token *token)
{
	if (!token)
		return (0);
	if (token->type == TK_DQ_STR || token->type == TK_SQ_STR)
		return (1);
	return (0);
}
