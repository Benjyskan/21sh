#include "tosh.h"
#include "lexer.h"
#include "ast.h"

t_bool	is_ctrl_op_token(t_token *token)
{
	if (token->type >= TK_AND)
		return (1);
	return (0);
}

void	print_ast(t_ast *root)
{
	if (!root)
		return ;
	print_ast(root->left);
	print_token_list(root->token);
	print_ast(root->right);
}
