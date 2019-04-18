#include "lexer.h"
#include "libterm.h"
#include "reader.h"
#include "ast.h"

static t_bool	is_full_of_whitespaces(char *input)
{
	int		i;//TODO protect

	i = -1;
	while (input[++i])
	{
		if (!is_white_spaces(input[i]))
			return (0);
	}
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	char	**env_cpy;
	char	*input;
	//should declare cmd_struct here

	(void)argc;
	(void)argv;
	if (setup_terminal_settings() == -1)
		return (EXIT_FAILURE);
	if (!(env_cpy = init_env(env)))
		return (EXIT_FAILURE);
	while (42)
	{
		if (!(input = input_loop()))
			break ; // free env
		//store input in history here
		if (is_full_of_whitespaces(input))
		{
			ft_memdel((void*)&input);
			continue ;
		}
		if (!handle_input(input, env_cpy))
			ft_memdel((void*)&input);
	}
	ft_free_ntab(env_cpy);
	print_line();
	if (reset_terminal_settings())
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
