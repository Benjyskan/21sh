#include "21sh.h"

static int	is_blank_or_column(char c)
{
	if (c == ' ' || c == '\t' || c == ';')
		return (1);
	return (0);
}

static char	*pad_with_zero(char *str, int i)
{
	char	*tmp;
	int		in_cmd;

	tmp = ft_strdup(str);
	while (is_blank_or_column(tmp[--i]))
		tmp[i] = 0;
	i = -1;
	while (is_blank_or_column(tmp[++i]))
		tmp[i] = 0;
	in_cmd = 1;
	while (tmp[i])
	{
		if (tmp[i] == ';')
			in_cmd = 0;
		if (is_blank_or_column(tmp[i]) && !in_cmd)
			tmp[i] = 0;
		else
			in_cmd = 1;
		i++;
	}
	return (tmp);
}

static int	get_cmd_count(char *str, int init_len)
{
	int		in_cmd;
	int		i;
	int		cmd_count;

	in_cmd = 0;
	i = 0;
	cmd_count = 0;
	while (i < init_len)
	{
		if (str[i] && !in_cmd)
		{
			in_cmd = 1;
			cmd_count++;
		}
		else if (!str[i] && in_cmd)
		{
			in_cmd = 0;
		}
		i++;
	}
	return (cmd_count);
}

static void	fill_tab(char *str, int tab_len, char ***tab)
{
	int		i;
	int		j;
	int		in_cmd;

	i = 0;
	while (!str[i])
		i++;
	j = 0;
	in_cmd = 1;
	while (j < tab_len)
	{
		if (!((*tab)[j++] = ft_strdup(&str[i])))
			ERROR_MEM;
		while (str[i])
			i++;
		while (!str[i])
			i++;
	}
	(*tab)[j] = 0;
}

char		**my_strsplit(char *str)
{
	int		init_len;
	int		cmd_count;
	char	*tmp;
	char	**res;

	init_len = ft_strlen(str);
	tmp = pad_with_zero(str, init_len);
	cmd_count = get_cmd_count(tmp, init_len);
	if (!(res = (char**)malloc(sizeof(char**) * (cmd_count + 1))))
		ERROR_MEM;
	fill_tab(tmp, cmd_count, &res);
	ft_memdel((void*)&tmp);
	return (res);
}
