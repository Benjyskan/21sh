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

/*
** struct
*/

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

/*
** enum
*/

typedef enum		e_token_type
{
	TK_IGNORE,
	TK_LITERAL,
	TK_SQ_STR,
	TK_DQ_STR,
	TK_REDIRECTION,
	TK_PIPE
}					t_token_type;
