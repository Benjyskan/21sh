#ifndef TOSH_H
# define TOSH_H

# include <stdio.h>//tejme

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/syslimits.h>
# include "libft.h"
# include "lexer.h"
# define BUF_SIZE 128
# define SHELL_NAME "my_sh"
# define FD_LIMITS 10
# define ERROR_MEM error_mem();
# define ERROR_READ exit(1);//TODO

typedef unsigned char	t_bool;

typedef enum		e_parser_state
{
	NORMAL,
	IN_CMD,
	IN_SQUOT,
	IN_DQUOT
}					t_parser_state;

typedef enum		e_lexer_state
{
	LEX_NORMAL,
	LEX_IN_SQUOT,
	LEX_IN_DQUOT
}					t_lexer_state;

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
void				syntax_error_near(t_token *token);
//void				error_mem(char *func_name);

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
** lexer.c
*/

t_token				*create_token(char *cmdline, size_t size, t_token_type type);
t_bool				add_token_to_list(t_token *current_token
					, t_token *prev_token, t_token **token_head);
t_token				*lexer(char *cmdline, char **env);

/*
** lexer_tools.c
*/

t_bool				is_quotes(char c);
t_bool				is_white_spaces(char c);
t_bool				is_shell_char(char c);
t_bool				is_delimiter(char c);
t_bool				is_metachar(char c);
t_bool				is_and_or_token(t_token *token);

#endif
