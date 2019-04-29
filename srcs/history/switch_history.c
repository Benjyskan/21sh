#include "history.h"

/*
**	Switches the content of the current st_cmd, updating it with the newcmd
**	string. Cuts the trailing \n in the process, making sure that the string
**	copied does not end with a newline characters.
**	Makes sure to free the previous string before updating, but does not
**	free the st_txt struct, simply updates it.
*/

static void	switch_st_cmd(t_st_cmd *st_cmd, char *newcmd)
{
	size_t		len;
	t_st_txt	*st_txt;

	if ((len = ft_strlen(newcmd)) > 0)
	{
		if (newcmd[len - 1] == '\n')
			len--;
	}
	st_txt = st_cmd->st_txt;
	free(st_txt->txt);
	if (!(st_txt->txt = ft_strndup(newcmd, len)))
		ERROR_MEM;
	st_txt->data_size = (size_t)ft_strlen(st_txt->txt);
	st_txt->malloc_size = st_txt->data_size + 1;
	st_txt->tracker = st_txt->data_size;
	move_cursor(st_cmd->start_pos.col, st_cmd->start_pos.row);
	ft_dprintf(g_dev_tty, "%s", st_txt->txt); // should be special write function 
}

/*
**	Gets the previous history in the hist_list, and calls switch_st_cmd,
**	switching the characters displayed on screen to those of the previous
**	history.
*/

void	get_previous_history(t_st_cmd *st_cmd)
{
	if (!st_cmd->hist_lst || !st_cmd->hist_lst->prev)
		ft_putstr_tty(BELL);
	else if (st_cmd->hist_lst->prev)
	{
		free(st_cmd->hist_lst->cpy);
		if (!(st_cmd->hist_lst->cpy = ft_strdup(st_cmd->st_txt->txt))) //protect
			ERROR_MEM;
		st_cmd->hist_lst = st_cmd->hist_lst->prev;
		switch_st_cmd(st_cmd, st_cmd->hist_lst->cpy);
	}
}

/*
**	Gets the next history in the hist_list, and calls switch_st_cmd, switching
**	the characters displayed on screen to those of the next history.
*/


void	get_next_history(t_st_cmd *st_cmd)
{
	if (!st_cmd->hist_lst || !st_cmd->hist_lst->next)
		ft_putstr_tty(BELL);
	else
	{
		free(st_cmd->hist_lst->cpy);
		if (!(st_cmd->hist_lst->cpy = ft_strdup(st_cmd->st_txt->txt))) //protect
			ERROR_MEM;
		st_cmd->hist_lst = st_cmd->hist_lst->next;
		switch_st_cmd(st_cmd, st_cmd->hist_lst->cpy);
	}
}
