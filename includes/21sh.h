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
** environ_utils.c
*/

int     get_envline_index(char *search, char **env);
char    *get_envline_value(char *search, char **env);
char    *get_envline(char *search, char **env);
void	set_env_var(char *var_name, char *var_value, char ***env);
//void    replace_env_var(char *var_name, char *var_value, char **env_line);
#endif
