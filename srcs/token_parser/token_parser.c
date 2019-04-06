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
	ast_root->tklst = NULL;
	ast_root->left = NULL;
	ast_root->right = NULL;
	return (ast_root);
}

t_ast	*create_ast_node(t_tklst *tklst_head, t_tklst *tklst_probe)
{
	t_ast	*new_cmd_node;
	t_ast	*new_op_node;

	if (tklst_probe)
	{
		if (!(new_op_node = (t_ast*)malloc(sizeof(*new_op_node))))
		{
			ft_putendl_fd("malloc failed in create_ast_node", 2);
			return (NULL);//TODO free nicely plz
		}
		new_op_node->tklst = tklst_probe;
		new_op_node->tklst->next = NULL;
	}
	if (!(new_cmd_node = (t_ast*)malloc(sizeof(*new_cmd_node))))
	{
		ft_putendl_fd("malloc failed in create_ast_node", 2);
		return (NULL);//TODO free nicely plz
	}
	//
	return (new_node);
}

t_bool	add_cmd_to_ast(t_tklst **tklst_head, t_ast **ast_root)
{
	t_tklst	*tklst_probe;
	t_ast	*new_node;

	tklst_probe = *tklst_head;
	while (tklst_probe && !is_ctrl_op_token(tklst_probe->token->type))
		tklst_probe = tklst_probe->next;
	//i'm at the end of tklst or on a ctrl_op token, so tklst_probe might be NULL
	if (!(new_node = create_ast_node(tklst_head, tklst_probe)))
		return (0);
	insert_ast_node(new_node, ast_root
	return (1);
}

t_ast	*token_parser(t_tklst *tklst_head)
{
	t_ast	*ast_root;

	if (!(ast_root = init_ast))//bof: autant checker et l'init dans add_cmd_to_ast
		return (NULL);
	while (tklst_head)
	{
		if (!(add_cmd_to_ast(&tklst_head, &ast_root)))
			return (NULL);//if fail: need to free the all ast
	}
	return (ast_root);
}
