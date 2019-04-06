#ifndef AST_H
# define AST_H

#include "tosh.h"
#include "lexer.h"

typedef enum		e_cmdtype
{
	SIMPLE_CMD = 1,
	PIPELINES
}					t_cmdtype;


typedef struct		s_ast//useless
{
	struct s_ast	*parent;
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
	//t_tklst			*tklst_head;
}					t_simplecmd;

/*
** t_pipelst
** is a list of simplecmd
** redirection will be set as we parse the pipelst ??
*/

typedef struct		s_pipelst
{
	t_simplecmd			*simplecmd;
	struct s_pipelst	*next;
}					t_pipelst;

/*
** token_parser.c
*/

t_ast			*token_parser(t_tklst *tklst_head);

/*
** Pipeline parsing
*/

int				parse_pipeline(t_tklst *tklst);
void			redirect(int old_fd, int new_fd);

int				is_simple_cmd_token(t_tklst *probe);
char			**get_argv_from_tokens(t_tklst *tklst);

#endif
