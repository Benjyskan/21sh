#include "21sh.h"

/*
** create_minienv
** malloc a minienv
** set SHLVL=1 and PWD
** and return it
*/

static char	**create_minienv(void)
{
	int		init_lines;
	char	**env;
	char	*cwd;

	init_lines = 3;
	if (!(env = (char**)malloc(sizeof(char**) * init_lines)))
		ERROR_MEM;
	if (!(env[0] = ft_strnew(7 + 8)))
		ERROR_MEM;
	ft_strcpy(env[0], "SHLVL=1");
	if (!(cwd = getcwd(NULL, 0)))
		ERROR_MEM;
	if (!(env[1] = ft_strnew(4 + ft_strlen(cwd))))
		ERROR_MEM;
	ft_strcpy(env[1], "PWD=");
	ft_strcpy(&env[1][4], cwd);
	env[init_lines - 1] = NULL;
	ft_memdel((void*)&cwd);
	return (env);
}

/*
** init_env
** return a copy of env if it exist and set_shlvl
** return a fresh minienv otherwise
*/

char		**init_env(char **env)
{
	char	**new_env;

	if (*env)
	{
		new_env = ft_dup_nultab(env);
		set_shlvl(&new_env);
		return(new_env);
	}
	else
		return(create_minienv());
	return (NULL);//TODO when do this happen ?
}
