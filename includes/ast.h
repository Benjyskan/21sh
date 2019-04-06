#ifndef AST_H
# define AST_H

#include "tosh.h"
#include "lexer.h"

typedef struct		s_ast//useless
{
	//struct s_ast	*parent;
	t_tklst			*tklst;
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
}					t_simplecmd

/*
** t_pipelst
** is a list of simplecmd
** redirection will be set as we parse the pipelst ??
*/

typedef struct		s_pipelst
{
	t_simplecmd		*simplecmd;
	t_pipelst		*next;
}					t_pipelst

/*
** token_parser.c
*/

t_ast			*token_parser(t_tklst *tklst_head);

#endif
