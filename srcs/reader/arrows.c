#include "reader.h"

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

void	move_vertically(t_cmd_struct *cmd_struct, char *direction)
{
	(void)cmd_struct;
	if (ft_strncmp(direction, "up", 3) == 0)
		ft_putstr_tty(UPARROW);
	else if (ft_strncmp(direction, "down", 5) == 0)
		ft_putstr_tty(DOWNARROW);
}
