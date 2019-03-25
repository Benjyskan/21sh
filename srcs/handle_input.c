#include "tosh.h"

static int	is_blank_or_column(char c)
{
	if (c == ' ' || c == '\t' || c == ';')
		return (1);
	return (0);
}

static int	check_cmdline_state(t_parser_state state)
{
	if (state == IN_SQUOT)
	{
		ft_putendl_fd("Unmatched '.", 2);
		return (0);
	}
	if (state == IN_DQUOT)
	{
		ft_putendl_fd("Unmatched \".", 2);
		return (0);
	}
	return (1);
}

/*
** add_cmdline_to_cmdlst
** create and add to cmdlst cmdline from input
** return (cmdline len)
** return 0 if it fail
*/

static int	add_cmdline_to_cmdlst(char *input, t_cmdlst **cmdlst_head)
{
	int				i;
	t_parser_state	state;

	i = 0;
	state = IN_CMD;
	while (input[i] && (input[i] != ';' || state >= IN_SQUOT))
	{// !! '/'
		if (input[i] == '\'' && state == IN_CMD
				&& ((i && input[i - 1] != '\\') || (i == 0)))
			state = IN_SQUOT;
		else if (input[i] == '\'' && state == IN_SQUOT)
			state = IN_CMD;

		else if (input[i] == '"' && state == IN_CMD
				&& ((i && input[i - 1] != '\\') || (i == 0)))
			state = IN_DQUOT;
		else if (input[i] == '"' && state == IN_DQUOT)//|| with similar check
			state = IN_CMD;

		else if (input[i] == '\\' && i && state == IN_CMD && input[i + 1])
		{
			ft_putendl("risky!!!");
			i++;//risky
		}
		i++;
	}
	if (!check_cmdline_state(state))
		return (0);
	if (!(add_to_cmdlst(ft_strndup(input, i), cmdlst_head)))
		return (0);
	return (i);
}

/*
** create_cmdlst_from_input
** return the head of the created cmdlst from input
** return 0 if it failed
*/

static int	create_cmdlst_from_input(char *input, char **env,
		t_cmdlst **cmdlst_head)
{
	int				i;
	int				tmp_int;
	t_parser_state	state;

	(void)env;
	i = -1;
	state = 0;
	while (input[++i])
	{
		if (!is_blank_or_column(input[i]))
		{
			if (!(tmp_int = add_cmdline_to_cmdlst(&input[i], cmdlst_head)))
			{
				free_cmdlst(*cmdlst_head);
				return (0);
			}
			i += tmp_int;
		}
	}
	ft_putendl("---------print cmdlst--------");
	print_cmdlst(*cmdlst_head);
	ft_putendl("-----------------------------");
	return (1);
}

/*
** handle_input
** add input to history
** send input to create_cmdlst_from_input
** 	return 0 if it fails
** free input
*/

int		handle_input(char *input, char **env)
{
	t_cmdlst	*cmdlst_head;

	cmdlst_head = NULL;
	//TODO add input to history, or do this in main (after readstdin)
	if (!(create_cmdlst_from_input(input, env, &cmdlst_head)))
	{
		return (0);
	}
	ft_memdel((void*)&input);

	//FOR EACH CMD
	//expand var (plus tard)
	//tokenize
	//lexer
	//exec tree

	//my_pipe(cmdlst_head->cmdline);//test

	free_cmdlst(cmdlst_head);
	return (1);
}
