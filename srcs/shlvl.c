#include "21sh.h"

void	set_shlvl(char ***env)
{
	char	*value;
	int		shlvl;
	char	*tmp;

	if ((value = get_envline_value("SHLVL", *env)))
	{
		shlvl = ft_atoi(value);
		if (shlvl < 0)
			set_env_var("SHLVL", "0", env);
		else if (shlvl == 0)
			set_env_var("SHLVL", "1", env);
		else
		{
			tmp = ft_itoa(shlvl + 1);
			set_env_var("SHLVL", tmp, env);
			ft_memdel((void*)&tmp);
		}
	}
	else
		set_env_var("SHLVL", "1", env);
}
