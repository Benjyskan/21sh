#ifndef TWENTYONESH_H
# define TWENTYONESH_H

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

/*
** main.c
*/

/*
** init_env.c
*/

char		**init_env(char **env);

/*
** errors.c
*/

void		error_mem(void);

/*
** shlvl.c
*/

void		set_shlvl(char ***env);

/*
** environ_utils.c
*/

int			get_envline_index(char *search, char **env);
char		*get_envline_value(char *search, char **env);
char		*get_envline(char *search, char **env);

/*
** environ_set.c
*/

void		set_env_var(char *var_name, char *var_value, char ***env);

/*
** prompt.c
*/

void		print_prompt(void);

/*
** my_strsplit.c
*/

char		**my_strsplit(char *str);

/*
** handle_input.c
*/

void		handle_input(char *input, char **env);
//t_cmdlst	*split_on_colomn(char *input, char **env);

/*
** cmd_lst_utils.c
*/

t_cmdlst	*create_cmdlst(char *cmdline);
void		add_to_cmdlst(char *cmdline, t_cmdlst *cmdlst_head);
void		print_cmdlst(t_cmdlst *head);

/*
** free.c
*/

void		free_cmdlst(t_cmdlst *cmdlst_head);
#endif
