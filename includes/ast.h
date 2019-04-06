#ifndef AST_H
# define AST_H

#include "tosh.h"
#include "lexer.h"

typedef struct		s_ast
{
	t_token			*token;
	struct s_ast	*left;
	struct s_ast	*right;
}					t_ast;

/*
** t_simplecmd
** is a list of tokens making a single cmd
** with a redirection table
*/

typedef struct		s_simplecmd
{
	int				redir_table[4];
	char			**cmd_table;
}					t_simplecmd;

/*
** token_parser.c
*/

//t_ast			*token_parser(t_token *token_head);
t_ast			*create_ast(t_token *token_head);

/*
** token_parser_utils.c
*/

t_bool			is_ctrl_op_token(t_token *token);

#endif
