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
	t_st_cmd		*st_cmd;

	(void)argc;
	(void)argv;
	if (setup_terminal_settings() == -1)
		return (EXIT_FAILURE);
	signal_setup();
	if (!(env_cpy = init_env(env)))
		return (EXIT_FAILURE);
	while (42)
	{
		st_cmd = init_st_cmd(env);
		if (!input_loop(st_cmd))
			break ; // free env, free st_cmd
		if (is_full_of_whitespaces(st_cmd->st_txt->txt) == 0)
			handle_input(st_cmd, env_cpy);
		//free st_cmd
	}
	write_to_history(st_cmd, env);
	//free st_cmd
	ft_free_ntab(env_cpy);
	print_line();
	if (reset_terminal_settings() == 0)
		return (EXIT_FAILURE);
	else
		return (EXIT_SUCCESS);
}
