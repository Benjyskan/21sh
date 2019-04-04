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

//typedef struct		s_cmdlst//useless
//{
//	char			*cmdline;
//	struct s_cmdlst	*next;
//}					t_cmdlst;

/*typedef enum		e_tk_type
{
	LITERAl,
	SQUOT_STR,
	DQUOT_STR
	//+
}					t_tk_type;*/

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

//int					add_to_cmdlst(char *cmdline, t_cmdlst **cmdlst_head);
//void				print_cmdlst(t_cmdlst *head);//debug

/*
** free.c
*/

//void				free_cmdlst(t_cmdlst *cmdlst_head);

/*
** test_pipe.c
*/

int					my_pipe(char *input);

/*
** lexer.c
*/

//int					lexer(t_cmdlst *cmdlst, char **env);
//t_tklst				lexer(t_cmdlst *cmdlst, char **env);
t_tklst				*lexer(char *cmdline, char **env);

/*
** lexer_tools.c
*/

t_bool				is_quotes(char c);
t_bool				is_white_spaces(char c);
t_bool				is_shell_char(char c);
t_bool				is_delimiter(char c);
t_bool				is_metachar(char c);

/*
** lexer_cmp_table.c
*/

t_op_chart			*get_op_chart(void);
void				print_op_table(t_op_chart *op_chart);//debug
#endif
