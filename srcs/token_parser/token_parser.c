#include "tosh.h"
#include "lexer.h"
#include "ast.h"

t_ast	*init_ast(void)
{
	t_ast	*ast_root;

	if (!(ast_root = (t_ast*)malloc(sizeof(*ast_root))))
	{
		ft_putendl_fd("malloc failed in init_ast", 2);
		return (NULL);
	}
	ast_root->token = NULL;
	ast_root->left = NULL;
	ast_root->right = NULL;
	return (ast_root);
}

t_ast	*create_ast_node(t_token *token_head, t_token *token_probe)
{
	t_ast	*new_cmd_node;
	t_ast	*new_op_node;

	if (token_probe)
	{
		if (!(new_op_node = (t_ast*)malloc(sizeof(*new_op_node))))
		{
			ft_putendl_fd("malloc failed in create_ast_node", 2);
			return (NULL);//TODO free nicely plz
		}
		new_op_node->token = token_probe;
		new_op_node->token->next = NULL;
	}
	if (!(new_cmd_node = (t_ast*)malloc(sizeof(*new_cmd_node))))
	{
		ft_putendl_fd("malloc failed in create_ast_node", 2);
		return (NULL);//TODO free nicely plz
	}
	//
	return (new_node);
}

t_bool	add_cmd_to_ast(t_token **token_head, t_ast **ast_root)
{
	t_token	*token_probe;
	t_ast	*new_node;

	token_probe = *token_head;
	while (token_probe && !is_ctrl_op_token(token_probe->token->type))
		token_probe = token_probe->next;
	//i'm at the end of token or on a ctrl_op token, so token_probe might be NULL
	if (!(new_node = create_ast_node(token_head, token_probe)))
		return (0);
	insert_ast_node(new_node, ast_root
	return (1);
}

t_ast	*token_parser(t_token *token_head)
{
	t_ast	*ast_root;

	if (!(ast_root = init_ast))//bof: autant checker et l'init dans add_cmd_to_ast
		return (NULL);
	while (token_head)
	{
		if (!(add_cmd_to_ast(&token_head, &ast_root)))
			return (NULL);//if fail: need to free the all ast
	}

	return (ast_root);
}
