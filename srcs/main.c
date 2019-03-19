#include "21sh.h"

int		main(int argc, char **argv, char **env)
{
	char	**env_cpy;

	(void)argc;
	(void)argv;
	//check args ?
	//init_env
	if (!(env_cpy = init_env(env)))
		return (1);//error
	//loop

	//
	//set_env_var("NEWNEW", "HEHEY", &env_cpy);
	ft_put_nultab(env_cpy);
	ft_free_nultab(env_cpy);
	//
	return (0);
}
