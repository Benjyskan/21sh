#include "tosh.h"
#include "lexer.h"
#include "ast.h"

t_bool	is_ctrl_op_token(t_token *token)
{
	if (token->type >= TK_AND)
		return (1);
	return (0);
}

t_bool	exec_ast(t_ast *root)
{
	if (!root)
		dprintf(2, "Error: NULL node\n");
	if (root->token->type == TK_SEMI)
	{
		exec_ast(root->left);
		return (exec_ast(root->right)); // check if that's true
	}
	else if (root->token->type == TK_AND)
		return (exec_ast(root->left) && exec_ast(root->right));
	else if (root->token->type == TK_OR)
		return (exec_ast(root->left) || exec_ast(root->right));
	else
		return (parse_pipeline(root->token));
}

void	print_ast(t_ast *root)
{
	if (!root)
		return ;
	print_ast(root->left);
	print_token_list(root->token);
	print_ast(root->right);
}
