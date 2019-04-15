#include "tosh.h"
#include "lexer.h"
#include "ast.h"

t_bool	is_ctrl_op_token(t_token *token)
{
	if (token->type >= TK_AND)
		return (1);
	return (0);
}

t_bool	exec_ast(t_ast *root, char **env)
{
	if (!root)
		dprintf(2, "Error: NULL node\n");
	if (root->token->type == TK_SEMI)//TK_AMP
	{
		exec_ast(root->left, env);
		if (root->right)//penzo added this
			return (exec_ast(root->right, env)); // check if that's true
		else
			return (1);//penzo test
	}
	else if (root->token->type == TK_AND)
		return (exec_ast(root->left, env) || exec_ast(root->right, env));
	else if (root->token->type == TK_OR)
		return (exec_ast(root->left, env) && exec_ast(root->right, env));
	else
		return (parse_pipeline(root->token, env));
}

void	print_ast(t_ast *root)
{
	if (!root)
		return ;
	print_ast(root->left);
	print_token_list(root->token);
	print_ast(root->right);
}
