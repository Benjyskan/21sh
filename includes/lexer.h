#ifndef LEXER_H
# define LEXER_H

# include <stdio.h>//tejme

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/syslimits.h>
# include "libft.h"
# define ERROR_MEM error_mem();

typedef unsigned char	t_bool;

typedef enum		e_token_type
{
	TK_WSPACE,
	TK_LITERAL,//1
	TK_SQ_STR,
	TK_DQ_STR,
	TK_REDIRECTION,
	TK_PIPE,
	//TK_SEMI,
	//TK_AND
	//TK_OR
	//TK_AMP
	TK_CTRL_OP,
	TK_42SH
}					t_token_type;

typedef struct		s_token
{
	char			*content;
	size_t			size;
	t_token_type	type;
	t_bool			is_delimited;
}					t_token;

typedef struct		s_tklst
{
	t_token			*token;
	struct s_tklst	*next;
}					t_tklst;

typedef struct		s_operation
{
	char			str[4];
	unsigned char	size;
	t_token_type	type;
}					t_operation;

# define OP_CHART_SIZE 22

typedef struct		s_op_chart
{
	t_operation		op_chart[OP_CHART_SIZE];
}					t_op_chart;

//DEBUG TEJME
void	print_token(t_token *token);//debug
void	print_token_list(t_tklst *tklst_head);

/*
** get_token.c
*/

t_token	*get_dquot_token(char **cmdline);
t_token	*get_squot_token(char **cmdline);
t_token	*get_regular_token(char **cmdline);
t_token	*get_redir_token(char **cmdline);
t_token	*get_monochar(char **cmdline);
t_token	*check_if_redir_or_literal(char **cmdline);
t_token	*get_token(char **cmdline, t_op_chart *op_chart);

/*
** tklst_utils.c
*/

t_token	*create_token(char *cmdline, size_t size, t_token_type type);
t_tklst	*create_tklst_node(t_token *token); //static ? 
t_bool	add_token_to_tklst(t_token *token, t_tklst **tklst_head);

/*
** lexer_op_chart.c
*/

t_token	*cmp_with_op_chart(char **cmdline, t_op_chart *op_chart);

#endif
