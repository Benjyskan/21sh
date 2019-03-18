#include "21sh.h"

/*
** ft_strcmp_before_c
** return "c offset" if search==str before the c char in str
** return 0 otherwise
*/

int		ft_strcmp_before_c(char *search, char *str, char c)
{
	int		i;

	if (!search || !str || !c)
		return (0);
	i = -1;
	while (str[++i] != c && search[i])
	{
		if (str[i] != search[i])
			return (0);
	}
	if (!search[i] && str[i] == c)
		return (i);
	else
		return (0);
}

/*
** get_envline_index
** return the index of the searched variable
** return -1 if not found
*/

int		get_envline_index(char *search, char **env)
{
	int	i;

	i = -1;
	while (env[++i])
	{
		if (ft_strcmp_before_c(search, env[i], '='))
			return (i);
	}
	return (-1);
}

/*
** get_envline_value
** return a pointer to the envline after '='
** return NULL otherwise
*/

char	*get_envline_value(char *search, char **env)
{
	int		i;
	int		offset;

	i = -1;
	while (env[++i])
	{
		if ((offset = ft_strcmp_before_c(search, env[i], '=')))
			return (&(env[i][offset + 1]));
	}
	return (NULL);
}

/*
** get_envline
** return a pointer to the searched envline
** return NULL otherwise
*/

char	*get_envline(char *search, char **env)
{
	int		i;

	i = -1;
	while (env[++i])
	{
		if (ft_strcmp_before_c(search, env[i], '='))
			return (env[i]);
	}
	return (NULL);
}

/*
** replace_env_var
** replace an existing env[line] via address "&env[i]"
*/

static void	replace_env_var(char *var_name, char *var_value, char **env_line)
{
	int		new_len;
	int		var_name_len;

	ft_memdel((void*)&(*env_line));
	new_len = ft_strlen(var_name) + ft_strlen(var_value) + 1;
	if (!(*env_line = ft_strnew(new_len)))
		ERROR_MEM;
	ft_strcpy(*env_line, var_name);
	var_name_len = ft_strlen(var_name);
	(*env_line)[var_name_len] = '=';
	ft_strcpy(&(*env_line)[var_name_len + 1], var_value);
}

/*
** add_env_var
** realloc env via pointer, with a new line
*/

static void	add_env_var(char *var_name, char *var_value, char ***env)
{
	char	**new_env;
	int		env_len;
	int		i;

	env_len = get_ntab_len(*env);
	if (!(new_env = (char**)malloc(sizeof(char**) * (env_len + 2))))
		ERROR_MEM;
	i = -1;
	while ((*env)[++i])
	{
		if (!(new_env[i] = ft_strdup((*env)[i])))
			ERROR_MEM;
	}
	if (!(new_env[i] = (char*)malloc(sizeof(char*))))
		ERROR_MEM;
	replace_env_var(var_name, var_value, &new_env[i]);
	new_env[i + 1] = NULL;
	ft_free_nultab(*env);
	*env = new_env;
}

/*
** set_env_var
** check if var_name already exist in env
** if so, replace the line with another mallocated on
** else, realloc env to add a new line
*/

void	set_env_var(char *var_name, char *var_value, char ***env)
{
	int		index;

	if ((index = get_envline_index(var_name, *env)) != -1)
		replace_env_var(var_name, var_value, &(*env)[index]);
	else
		add_env_var(var_name, var_value, env);
}
