#include "tosh.h"
#include "lexer.h"
#include "ast.h"

void	free_token_list(t_token *token_head)
{
	t_token	*probe;

	probe = token_head;
	while (probe)
	{
		probe = probe->next;
		free(token_head->content);
		ft_memdel((void*)&token_head);
		token_head = probe;
	}
	ft_putendl("end of free_token_list");
}

void	free_ast(t_ast *ast_root)
{
	if (ast_root->left)
		free_ast(ast_root->left);
	//do stuff
	free_token_list(ast_root->token);
	if (ast_root->right)
		free_ast(ast_root->right);
}
