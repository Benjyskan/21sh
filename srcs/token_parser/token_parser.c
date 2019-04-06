#include "tosh.h"
#include "lexer.h"
#include "ast.h"

t_ast	*init_ast(t_ast *new_node, t_token *token_head, t_ast *ast_root)
{
	new_node->token = token_head;
	new_node->left = NULL;
	new_node->right = NULL;
	ast_root = new_node;
	return (ast_root);
}

t_ast	*insert_ast_node(t_token *token_head, t_ast **ast_root)
{
	t_token_type	new_node_weight;
	t_ast			*new_node;
	t_ast			*ast_probe;

	printf("In insert_ast_node: %s\n", token_head->content);
	if (!(new_node = (t_ast*)malloc(sizeof(*new_node))))
	{
		ft_putendl_fd("malloc failed in insert_ast_node", 2);
		return (NULL);
	}
	if (*ast_root == NULL)
		return (init_ast(new_node, token_head, *ast_root));
	new_node_weight = token_head->type;//get first token weight
	new_node->token = token_head;
	//find placement (need recusrion)
	ast_probe = *ast_root;
	if (new_node_weight >= (*ast_root)->token->type)
	{
		*ast_root = new_node;//reroot
		(*ast_root)->left = ast_probe;
	}
	else if (new_node_weight < (*ast_root)->token->type)
	{
		ast_probe->right = new_node;
	}
	return (*ast_root);//tmp
}

t_bool	add_node_to_ast(t_token **token_head, t_ast **ast_root)
{
	t_token	*token_probe;
	t_token	*token_prev;
	t_ast	*ast_probe;

	token_probe = *token_head;
	ast_probe = *ast_root;
	while (token_probe && !(is_ctrl_op_token(token_probe)))
	{
		token_prev = token_probe;
		token_probe = token_probe->next;
	}
	if (!token_probe)//end of tklst
	{
		*ast_root = insert_ast_node(*token_head, ast_root);
		*token_head = NULL;//check me
		return (1);
	}
	else
	{
		//here: verif if "&& &&"
		token_prev->next = NULL;
		*ast_root = insert_ast_node(*token_head, ast_root);
		*token_head = token_probe->next;
		token_probe->next = NULL;
		*ast_root = insert_ast_node(token_probe, ast_root);
		if (*token_head == NULL)
			return (0);//error
	}
	return (1);
}

t_ast	*create_ast(t_token *token_head)
{
	t_ast	*ast_root;

	ast_root = NULL;
	while (token_head)
	{
		if (!(add_node_to_ast(&token_head, &ast_root)))
			return (NULL);//free ast
	}
	return (ast_root);
}
