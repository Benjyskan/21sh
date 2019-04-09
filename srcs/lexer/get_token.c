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
		i++;
	}
	if ((*cmdline)[i] == 0)
	{
		ft_putendl_fd("Unmatched \". READ_MODE PLZ", 2);
		return (NULL);
	}
	if (!(token = create_token(*cmdline, ++i, TK_DQ_STR)))
		return (NULL);
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
		ft_putendl_fd("Unmatched '. READ_MODE PLZ", 2);
		return (NULL);
	}
	if (!(token = create_token(*cmdline, ++i, TK_SQ_STR)))
		return (NULL);
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
		return (NULL);
	*cmdline = *cmdline + i;
	return (token);
}

static t_token	*get_monochar(char **cmdline)
{
	t_token	*token;

	(*cmdline)++;
	if (!(token = create_token(*cmdline, 1, TK_WORD)))
		return (NULL);
	//if '\''\n' continue reading ?
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
		return (NULL);
	*cmdline = *cmdline + i;
	return (token);
}

t_token			*get_token(char **cmdline, t_operation *op_chart)
{
	t_token	*token;

	//should i strncmp(*cmdline with a table of pattern ??
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
