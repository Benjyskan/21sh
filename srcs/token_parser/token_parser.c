#include "tosh.h"
#include "lexer.h"
#include "ast.h"

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

t_bool	null_terminat_properly(t_token *token)
{
	if (!token)
		return (0);
	if (!(token->next))
		return (1);
	while (token->next->type == TK_EAT)
		token = token->next;
	ft_putendl("null terminating");//tmp
	token->next = NULL;
	return (1);
}

t_bool	add_node_to_ast(t_token **token_head, t_ast **ast_root)
{
	t_token	*token_probe;
	t_token	*token_prev;
	t_ast	*ast_probe;

	token_probe = *token_head;
	ast_probe = *ast_root;
	token_prev = NULL;
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
		if (*token_head == token_probe || !null_terminat_properly(token_prev))//verif if "&& &&"//useless if i check in lexer
		{
			ft_putstr("ICICI");
			syntax_error_near(token_probe);
			return (0);
		}
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
		//ft_putendl("***************");
		if (!(add_node_to_ast(&token_head, &ast_root)))
			return (NULL);//free ast
	}
	return (ast_root);
}
