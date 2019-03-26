#ifndef TOSH_H
# define TOSH_H

# include <stdio.h>//tejme

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/syslimits.h>
# include "libft.h"
# define BUF_SIZE 128
# define SHELL_NAME "my_sh"
# define ERROR_MEM error_mem();
# define ERROR_READ exit(1);//TODO

typedef unsigned char	t_bool;

typedef struct		s_cmdlst
{
	char			*cmdline;
	struct s_cmdlst	*next;
}					t_cmdlst;

typedef struct		s_tklst
{
	t_token			token;
	struct s_tklst	*next;
}					t_tklst;

typedef enum		e_token_type
{
	TK_IGNORE,
	TK_LITERAL,
	TK_SQ_STR,
	TK_DQ_STR,
	TK_REDIRECTION,
	TK_PIPE
}					t_token_type;

typedef struct		s_token
{
	char			*content;
	unsigned int	size;
	t_token_type	type;
	t_bool			is_delimited;
}					t_token;

typedef enum		e_parser_state
{
	NORMAL,
	IN_CMD,
	IN_SQUOT,
	IN_DQUOT
}					t_parser_state;

/*
** main.c
*/

/*
** init_env.c
*/

char				**init_env(char **env);

/*
** errors.c
*/

void				error_mem(void);

/*
** shlvl.c
*/

void				set_shlvl(char ***env);

/*
** environ_utils.c
*/

int					get_envline_index(char *search, char **env);
char				*get_envline_value(char *search, char **env);
char				*get_envline(char *search, char **env);

/*
** environ_set.c
*/

void				set_env_var(char *var_name, char *var_value, char ***env);

/*
** prompt.c
*/

void				print_prompt(void);

/*
** handle_input.c
*/

t_bool				handle_input(char *input, char **env);

/*
** cmd_lst_utils.c
*/

int					add_to_cmdlst(char *cmdline, t_cmdlst **cmdlst_head);
void				print_cmdlst(t_cmdlst *head);//debug

/*
** free.c
*/

void				free_cmdlst(t_cmdlst *cmdlst_head);

/*
** test_pipe.c
*/

int					my_pipe(char *input);

/*
** lexer_tools.c
*/

t_bool				is_quotes(char c);
t_bool				is_white_spaces(char c);
t_bool				is_shell_char(char c);
#endif
