#include "tosh.h"
#include "reader.h"

static void	switch_cmd_struct(t_cmd_struct *cmd_struct, char *newcmd)
{
	size_t	len;
	char	*tmp;

	len = ft_strlen(newcmd);
	if (newcmd[len - 1] == '\n')
		len--;
	tmp = cmd_struct->txt;
	if (!(cmd_struct->txt = ft_strndup(newcmd, len)))
		ERROR_MEM;
	ft_memdel((void*)&tmp);
	cmd_struct->total_data_size = len;
	cmd_struct->append_txt = cmd_struct->txt;
	cmd_struct->total_malloc_size = len;
	cmd_struct->current_data_size = len;
	cmd_struct->tracker = len;
	move_cursor(cmd_struct->start_pos.col, cmd_struct->start_pos.row);
	execute_str(CLEAR_BELOW);
	print_prompt(cmd_struct);
	ft_dprintf(g_dev_tty, "%s", cmd_struct->append_txt);
//	reposition_cursor(cmd_struct);
}

void	move_arrow_right(t_cmd_struct *cmd_struct)
{
	if (cmd_struct->tracker < cmd_struct->current_data_size)
		cmd_struct->tracker++;
	else
		ft_putstr_tty(BELL);
}

void	move_arrow_left(t_cmd_struct *cmd_struct)
{
	if (cmd_struct->tracker > 0)
	{
		cmd_struct->tracker--;
		reposition_cursor(cmd_struct);
	}
	else
		ft_putstr_tty(BELL);
}

void	replace_hist_lst(t_hist_lst *new, t_hist_lst *old)
{
	new->next = old->next;
	new->prev = old->prev;
	//free old;
}

void	get_previous_history(t_cmd_struct *cmd_struct)
{
	char	*tmp;

	if (!cmd_struct->hist_lst)
		ft_putstr_tty(BELL);
	else if (cmd_struct->hist_lst->prev)
	{
		tmp = cmd_struct->hist_lst->cpy;
		cmd_struct->hist_lst->cpy = ft_strdup(cmd_struct->txt); //protect
		ft_memdel((void*)&tmp);
		cmd_struct->hist_lst = cmd_struct->hist_lst->prev;
		switch_cmd_struct(cmd_struct, cmd_struct->hist_lst->cpy);
	}
	else
		ft_putstr_tty(BELL);
}

void	get_next_history(t_cmd_struct *cmd_struct)
{
	char	*tmp;

	if (!cmd_struct->hist_lst)
		ft_putstr_tty(BELL);
	else if (cmd_struct->hist_lst->next)
	{
		tmp = cmd_struct->hist_lst->cpy;
		cmd_struct->hist_lst->cpy = ft_strdup(cmd_struct->txt); //protect
		ft_memdel((void*)&tmp);
		cmd_struct->hist_lst = cmd_struct->hist_lst->next;
		switch_cmd_struct(cmd_struct, cmd_struct->hist_lst->cpy);
	}
	else
		ft_putstr_tty(BELL);
}

