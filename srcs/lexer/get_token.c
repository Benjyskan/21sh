#include "tosh.h"
#include "lexer.h"

static t_token	*get_dquot_token(t_cmd_struct *cmd_struct)
{
	t_token	*token;
	size_t	i;

	i = 1;
	while ((cmd_struct->txt)[i] && (cmd_struct->txt)[i] != '"')
	{
		if ((cmd_struct->txt)[i] == '\\')
			i++;
		if ((cmd_struct->txt)[i] == 0)
		{
			//ft_putendl("end with '\\', READ_MODE");
			ft_endl_tty("end with '\\', READ_MODE");
			(cmd_struct->txt)[i - 1] = 0;
			return (NULL);
		}
		i++;
	}
	if ((cmd_struct->txt)[i] == 0)
	{
		//ft_putendl_fd("Unmatched \". READ_MODE PLZ", 2);
		ft_endl_tty("Unmatched \". READ_MODE PLZ");
		(cmd_struct->txt)[i] = '\n';//test: seems good
		return (NULL);
	}
	if (!(token = create_token(cmd_struct->txt, ++i, TK_DQ_STR)))
		ERROR_MEM;
	cmd_struct->txt = cmd_struct->txt + i;
	return (token);
}

static t_token	*get_squot_token(t_cmd_struct *cmd_struct)
{
	t_token	*token;
	size_t	i;

	i = 1;
	while ((cmd_struct->txt)[i] && (cmd_struct->txt)[i] != '\'')
		i++;
	if ((cmd_struct->txt)[i] == 0)
	{
		//ft_putendl_fd("Unmatched '. READ_MODE PLZ", 2);
		ft_endl_tty("Unmatched '. READ_MODE PLZ");
		(cmd_struct->txt)[i] = '\n';//test: seems good
		(cmd_struct->txt)[i + 1] = '\0';//test
		return (NULL);
	}
	if (!(token = create_token(cmd_struct->txt, ++i, TK_SQ_STR)))
		ERROR_MEM;
	cmd_struct->txt = cmd_struct->txt + i;
	return (token);
}

static t_token	*get_regular_token(t_cmd_struct *cmd_struct)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while ((cmd_struct->txt)[i] && !is_metachar((cmd_struct->txt)[i]))
		i++;
	if (!(token = create_token(cmd_struct->txt, i, TK_WORD)))
		ERROR_MEM;
	cmd_struct->txt = cmd_struct->txt + i;
	return (token);
}

static t_token	*get_monochar(t_cmd_struct *cmd_struct)
{
	t_token	*token;

	//(cmd_struct->txt)++;
	if (*(cmd_struct->txt + 1) == 0)
	{
		ft_endl_tty("end with '\\', READ_MODE");
		//(cmd_struct->txt)--;
		*cmd_struct->txt = 0;//test: seems good
		cmd_struct->tracker--;
		cmd_struct->current_data_size--;
		return (NULL);
	}
	(*cmdline)++;
	if (!(token = create_token(*cmdline, 1, TK_MONOC)))
		ERROR_MEM;
	dprintf(g_dev_tty, "get_monochar returned: {%s}\n", token->content);print_line();
	(*cmdline)++;
	return (token);
}

static t_token	*get_eat_token(t_cmd_struct *cmd_struct)
{
	t_token	*token;
	size_t	i;

	i = 0;
	while (is_white_spaces((cmd_struct->txt)[i]))
		i++;
	if (!(token = create_token(cmd_struct->txt, i, TK_EAT)))
		ERROR_MEM;
	cmd_struct->txt = cmd_struct->txt + i;
	return (token);
}

t_token			*get_token(t_cmd_struct *cmd_struct, t_operation *op_chart)
{
	t_token	*token;

	dprintf(g_dev_tty, "in get_token: {%s}", cmd_struct->txt);print_line();
	//system("read -p \"Press enter to continue\"");
	if (*cmd_struct->txt == '"')
		return (get_dquot_token(cmd_struct));
	else if (*cmd_struct->txt == '\'')
		return (get_squot_token(cmd_struct));
	else if (*cmd_struct->txt == '\\')
		return (get_monochar(cmd_struct));
	else if (is_white_spaces(*cmd_struct->txt))
		return (get_eat_token(cmd_struct));
	else if ((token = get_op_chart_token(cmd_struct, op_chart)))
		return (token);
	else//bof, need other conditions
		return (get_regular_token(cmd_struct));
}
