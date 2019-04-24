#include "tosh.h"
#include "lexer.h"
#include "ast.h"

/*
** create_ast_node
** malloc a new ast_node
*/

static t_ast	*create_ast_node(t_token *new_token, t_ast *left, t_ast *right)
{
	t_ast	*new_node;

	if (!(new_node = (t_ast*)malloc(sizeof(*new_node))))
		ERROR_MEM;
	new_node->token = new_token;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

/*
** reroot_ast
** shift the current node to the left
** and place the new_token as root
*/

static t_bool	reroot_ast(t_token *new_token, t_ast **ast_root)
{
	if (!(*ast_root = create_ast_node(new_token, *ast_root, NULL)))
		return (0);
	return (1);
}

/*
** insert_ast_node
** recursively look for the correct spot to add node in ast
** 1. check if current spot is empty, insert here
** 2. check if new->type is >= current->type, if so:
** 	reroot current to new
** 3. if left is empty, insert left
** 4. insert right
*/

static t_bool	insert_ast_node(t_ast *new_ast_node, t_ast **ast_root)
{
	if (!*(ast_root))
	{
		*ast_root = new_ast_node;
		return (1);
	}
	if (new_ast_node->token->type >= (*ast_root)->token->type)//reroot
	{
		new_ast_node->left = *ast_root;
		*ast_root = new_ast_node;
		return (1);
	}
	else
	{
		if (!(*ast_root)->left)
			return (insert_ast_node(new_ast_node, &(*ast_root)->left));
		else
			return (insert_ast_node(new_ast_node, &((*ast_root)->right)));
	}
}

/*
** null_terminate_properly
** just parse EAT tokens and null terminated the token_list
*/

static void	null_terminate_properly(t_token *token)
{
	if (!token || !(token->next))
		return ;
	while (token->next->type == TK_EAT)
		token = token->next;
	token->next = NULL;
	return ;
}

/*
** is_tklst_full_eat
** just check if the given token list is full of eat tokens
*/

static t_bool	is_tklst_full_eat(t_token *token_head)
{
	t_token	*probe;

	probe = token_head;
	while (probe)
	{
		if (probe->type > TK_EAT)
			return (0);
		probe = probe->next;
	}
	return (1);
}

static t_bool	add_node_to_ast(t_token **token_head, t_ast **ast_root)
{
	t_token	*token_probe;
	t_token	*token_prev;
	t_ast	*ast_probe;

	token_probe = *token_head;//make init_add_node ??
	ast_probe = *ast_root;    //
	token_prev = NULL;        //
	while (token_probe && !(is_ctrl_op_token(token_probe)))//make func ?
	{                                                      //
		if (token_probe->type != TK_EAT)                   //
			token_prev = token_probe;                      //
		token_probe = token_probe->next;                   //
	}                                                      //
	if (!token_probe)//end of token list  //make func ?
	{
		if (!is_tklst_full_eat(*token_head))
		{
			if (!(insert_ast_node(create_ast_node(*token_head, NULL, NULL), ast_root)))
				return (0);
		}
		else
			free_token_list(*token_head);
		*token_head = NULL;
		return (1);
	}
	else//i'm on a CTRL_OP
	{
		null_terminate_properly(token_prev);
		if (!(insert_ast_node(create_ast_node(*token_head, NULL, NULL), ast_root)))
			return (0);
		*token_head = token_probe->next;
		token_probe->next = NULL;
		if (!(insert_ast_node(create_ast_node(token_probe, NULL, NULL), ast_root)))
			return (0);
	}
	return (1);
}

/*
** create_ast
** run through token_list and create ast from it
** each add_node_to_ast:
** - add 2 node to ast, 1 simple_cmd and 1 ctrl_op (except the last call)
** - move the token_head accordingly
*/

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
