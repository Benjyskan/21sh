#include "lexer.h"
#include "libterm.h"
#include "reader.h"
#include "ast.h"
#include "history.h"

t_bool	is_full_of_whitespaces(char *input)
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
	char			**env_cpy;
	t_cmd_struct	*cmd_struct;

	(void)argc;
	(void)argv;
	if (setup_terminal_settings() == -1)
		return (EXIT_FAILURE);
	signal_setup();
	if (!(env_cpy = init_env(env)))
		return (EXIT_FAILURE);
	cmd_struct = init_cmd_struct(env);
	while (42)
	{
		if (!(cmd_struct = input_loop(cmd_struct)))
			break ; // free env, free char *
		//store input in history here
		if (is_full_of_whitespaces(cmd_struct->txt))
		{
			reset_cmd_struct(cmd_struct);
			continue;
		}
		if (!(handle_input(cmd_struct, env_cpy)))
			;
			//free cmd_struct
			//ft_memdel((void*)&input);
		reset_cmd_struct(cmd_struct);
	}
	ft_free_ntab(env_cpy);
	print_line();
	if (reset_terminal_settings())
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
