#include "tosh.h"
#include "lexer.h"
#include "ast.h"

/*
static t_token	*token_dup(t_token *token)
{
	t_token		*new_token;

	if (!(new_token = (t_token*)malloc(sizeof(t_token))))
		return (NULL);
	if (!(new_token->content = ft_strndup(token->content, token->size)))
		return (NULL);//free new_token
	new_token->size = token->size;
	new_token->type = token->type;
	new_token->is_delimited = token->is_delimited;
	return (new_token);
}

static t_ast	*create_ast_node(t_token *token, t_ast *parent, t_ast *left,
		t_ast *right)
{
	t_ast	*new_node;

	if (!(new_node = (t_ast*)malloc(sizeof(t_ast))))
		return (NULL);
	if (!(new_node->token = token_dup(token)))
		return (NULL);
	new_node->parent = parent;
	new_node->left = left;
	new_node->right = right;
	return (new_node);
}

t_ast			*token_parser(t_tklst *tklst_head)
{
	t_ast	*ast_head;

	if (!(ast_head = create_ast_node(tklst_head->token, NULL, NULL, NULL)))
		return (NULL);
	printf("---AST---\n");
	print_token(ast_head->token);
	return (ast_head);
}
*/

/*t_ast	*init_ast(t_cmdtype *cmdtype, t_ast *next)
{
	t_ast	*new_node;

	if (!(new_node = (t_ast*)malloc(sizeof(t_ast))))
		return (NULL);
	new_node->cmdtype = cmdtype;
	new_node->next = next;
	return (new_node);
}

void	create_redirection_table(t_tklst *tklst_head)
{
	t_tklst	*tklst_probe;
	t_tklst	*prev_token;

	tklst_probe = tklst_head;
	prev_token = NULL;
	while (tklst_probe->token->type != TK_CTRL_OP)//TODO make a function to check if token type if ctrl_op
	{
		if (tklst_probe->token->type == TK_WORD)
		{
			prev_token = tklst_probe;
			tklst_probe = tklst_probe->next;
			//continue ;
		}
		else if (is_redir_op(tklst_probe->token->type))
	}
}*/

/*
** token_parser
** create a linked list of simple_cmd
** for each simple_cmd:
** -create a cmd_table (args list)
** -create a redir_table
**
** for pipes:
** -create a list of simple_cmd
** -create the redir_table of each cmd accordingly
*/

/*t_ast	*token_parser(t_tklst *tklst_head)
{
	t_ast	*ast_head;
	t_ast	*ast_probe;
	t_tklst	*tklst_probe;
	//t_tklst	*prev_token;

	if (!(ast_head = init_ast(NULL, NULL)))
		return (NULL);
	ast_probe = ast_head;
	tklst_probe = tklst_head;
	prev_token = NULL;//usefull ?
	//while !token_end
	while (tklst_probe)
	{
		init_sim...
		//parse tklst until a ctrl_op token, and keep track of previous token ?
		//create redir table first and and remove all used token
		create_redirection_table(tklst_head);
		//create cmd_table with left tokens
		create_cmd_table(tklst_head);
		//add tables to simple_cmd list
		//move 
	}

	//!!!!!PIPE!!!!
	return (ast_head);
}*/
