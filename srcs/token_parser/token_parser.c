#include "tosh.h"
#include "lexer.h"
#include "ast.h"

/*
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
*/

t_ast	*create_ast_node(t_token *new_token, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	if (!(new_node = (t_ast*)malloc(sizeof(*new_node))))
		ERROR_MEM;
	new_node->token = new_token;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

t_bool	reroot_ast(t_token *new_token, t_ast **ast_root)
{
	if (!(*ast_root = create_ast_node(new_token, *ast_root, NULL)))
		return (0);
	return (1);
}

t_bool	insert_ast_node(t_token *new_token, t_ast **ast_root)
{
	t_ast			*new_node;

	new_node = create_ast_node(new_token, NULL, NULL);
	if (!*(ast_root))
	{
		*ast_root = new_node;
		return (1);
	}
	if (new_token->type  >= (*ast_root)->token->type)
		return (reroot_ast(new_token, ast_root));
	else
	{
		if (!(*ast_root)->left)
			return (insert_ast_node(new_token, &(*ast_root)->left));
		else
			return (insert_ast_node(new_token, &((*ast_root)->right)));
	}
}

void	null_terminat_properly(t_token *token)
{
	if (!(token->next))
		return ;
	while (token->next->type == TK_EAT)
		token = token->next;
	ft_putendl("null terminating");
	token->next = NULL;
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
		if (token_probe->type != TK_EAT)//test
			token_prev = token_probe;
		token_probe = token_probe->next;
	}
	if (!token_probe)//end of tklst
	{
		insert_ast_node(*token_head, ast_root);
		*token_head = NULL;//check me
		return (1);
	}
	else//i'm on CTRL_OP
	{
		if (*token_head == token_probe)//verif if "&& &&"
		{
			ft_putendl("2 CTRL_OP a la suite");
			return (0);
		}

		//token_prev->next = NULL;//leak de TK_EAT!!
		null_terminat_properly(token_prev);

		insert_ast_node(*token_head, ast_root);
		*token_head = token_probe->next;
		token_probe->next = NULL;
		insert_ast_node(token_probe, ast_root);
		//if (*token_head == NULL)//why ?
		//	return (0);//error
	}
	return (1);
}

t_ast	*create_ast(t_token *token_head)
{
	t_ast	*ast_root;

	ast_root = NULL;
	while (token_head)
	{
		ft_putendl("***************");
		if (!(add_node_to_ast(&token_head, &ast_root)))
			return (NULL);//free ast
	}
	return (ast_root);
}
