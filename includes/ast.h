#ifndef AST_H
# define AST_H

#include "tosh.h"
#include "lexer.h"
#include <fcntl.h>

typedef struct		s_ast//useless
{
	//struct s_ast	*parent;
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

t_ast			*token_parser(t_token *token_head);

/*
** Pipeline parsing
*/

int				parse_pipeline(t_token *token);
void			redirect(int old_fd, int new_fd);

t_bool			is_simple_cmd_token(t_token *probe);
void			**get_argv_from_tokens(t_token *token);

t_bool			is_argv_token(t_token *probe);

/*
** Redirections parsing
*/

int				parse_redir(t_token *current, int fd_in, int fd_out);
int				parse_expands(t_token **argv);
#endif
