#include "reader.h"

void	move_arrow_left(t_cmd_line *cmd_struct)
{
	if (cmd_struct->position > 0)
	{
		ft_putstr_tty(LEFTARROW);
		cmd_struct->position -= 1;
	}
}

void	move_vertically(t_cmd_line *cmd_struct, char *direction)
{
	(void)cmd_struct;
	if (ft_strncmp(direction, "up", 3) == 0)
		ft_putstr_tty(UPARROW);
	else if (ft_strncmp(direction, "down", 5) == 0)
		ft_putstr_tty(DOWNARROW);
}
