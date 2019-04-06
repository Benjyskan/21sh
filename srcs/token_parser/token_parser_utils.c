#include "tosh.h"
#include "lexer.h"
#include "ast.h"

t_bool	is_ctrl_op_token(t_token *token)
{
	if (token->type >= TK_AND)
		return (1);
	return (0);
}
