#include "tosh.h"
#include "lexer.h"

static t_token	*get_dquot_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 1;
	while ((*cmdline)[i] && (*cmdline)[i] != '"')
	{
		if ((*cmdline)[i] == '\\')
			i++;
		if ((*cmdline)[i] == 0)
		{
			//ft_putendl("end with '\\', READ_MODE");
			ft_endl_tty("end with '\\', READ_MODE");
			(*cmdline)[i - 1] = 0;
			return (NULL);
		}
		i++;
	}
	if ((*cmdline)[i] == 0)
	{
		//ft_putendl_fd("Unmatched \". READ_MODE PLZ", 2);
		ft_endl_tty("Unmatched \". READ_MODE PLZ");
		(*cmdline)[i] = '\n';//test: seems good
		return (NULL);
	}
	if (!(token = create_token(*cmdline, ++i, TK_DQ_STR)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_squot_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 1;
	while ((*cmdline)[i] && (*cmdline)[i] != '\'')
		i++;
	if ((*cmdline)[i] == 0)
	{
		//ft_putendl_fd("Unmatched '. READ_MODE PLZ", 2);
		ft_endl_tty("Unmatched '. READ_MODE PLZ");
		(*cmdline)[i] = '\n';//test: seems good
		return (NULL);
	}
	if (!(token = create_token(*cmdline, ++i, TK_SQ_STR)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_regular_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while ((*cmdline)[i] && !is_metachar((*cmdline)[i]))
		i++;
	if (!(token = create_token(*cmdline, i, TK_WORD)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_monochar(char **cmdline)
{
	t_token	*token;

	(*cmdline)++;
	if (**cmdline == 0)
	{
		//ft_putendl("end with '\\', READ_MODE");
		ft_endl_tty("end with '\\', READ_MODE");
		(*cmdline)--;
		**cmdline = 0;//test: seems good
		dprintf(g_dev_tty, "after MONOCHAR: {%s}", *cmdline);
		print_line();
		return (NULL);
	}
	if (!(token = create_token(*cmdline, 1, TK_MONOC)))
		ERROR_MEM;
	dprintf(g_dev_tty, "get_monochar returned: {%s}\n", token->content);print_line();
	(*cmdline)++;
	return (token);
}

static t_token	*get_eat_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (is_white_spaces((*cmdline)[i]))
		i++;
	if (!(token = create_token(*cmdline, i, TK_EAT)))
		ERROR_MEM;
	*cmdline = *cmdline + i;
	return (token);
}

t_token			*get_token(char **cmdline, t_operation *op_chart)
{
	t_token	*token;

	//system("read -p \"Press enter to continue\"");
	if (**cmdline == '"')
		return (get_dquot_token(cmdline));
	else if (**cmdline == '\'')
		return (get_squot_token(cmdline));
	else if (**cmdline == '\\')
		return (get_monochar(cmdline));
	else if (is_white_spaces(**cmdline))
		return (get_eat_token(cmdline));
	else if ((token = get_op_chart_token(cmdline, op_chart)))
		return (token);
	else//bof, need other conditions
		return (get_regular_token(cmdline));
}
