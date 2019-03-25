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

typedef struct		s_cmdlst
{
	char			*cmdline;
	struct s_cmdlst	*next;
}					t_cmdlst;

typedef enum		e_token
{
	TK_PIPE = 1,
	TK_R_ARROW,
	TK_RD_ARROW,
	TK_L_ARROW,
	TK_LD_ARROW,
	TK_FD_REDI,
	TK_STR,
	TK_DQUOT_STR,
	TK_SQUOT_STR
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

int					handle_input(char *input, char **env);

/*
** cmd_lst_utils.c
*/

//t_cmdlst			*create_cmdlst_head(char *cmdline);
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
#endif
