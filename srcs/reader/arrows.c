#include "reader.h"

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

void	get_previous_history(t_cmd_struct *cmd_struct)
{
	(void)cmd_struct;
}

void	get_next_history(t_cmd_struct *cmd_struct)
{
	(void)cmd_struct;
}
