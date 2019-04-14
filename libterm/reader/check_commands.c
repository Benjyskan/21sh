#include "reader.h"

int		check_for_movement(t_input *input, char *buf)
{
	if (ft_strncmp(buf, RIGHTARROW, ARROW_LEN + 1) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(buf, LEFTARROW, ARROW_LEN + 1) == 0)
	{
		return (1);
	}
	else if (ft_strncmp(buf, UPARROW, ARROW_LEN + 1) == 0)
	{
		ft_putstr_tty(UPARROW); //
	}
	else if (ft_strncmp(buf, DOWNARROW, ARROW_LEN + 1) == 0)
	{
		ft_putstr_tty(DOWNARROW);
	}
	else
		return (0);
	return (1);
}

int		check_for_quit(char *buf)
{
	if (ft_strncmp(buf, CTRL_D, 2) == 0)
	{
		print_line();
		reset_terminal_settings();
		exit(0);
	}
	else
		return (0);
}

int		check_for_signal(char *buf)
{
	if (ft_strncmp(buf, CTRL_Z, 2) == 0)
	{
		ft_dprintf(2, "SHOULD BE BACKGROUND");
		print_line();
		return (1);
	}
	else
		return (0);
}

int		check_for_delete(t_input *input, char *buf)
{
	if (ft_strncmp(buf, BACKSPACE, BACKSPACE_LEN + 1) == 0)
		return (1);
	else
		return (0);
}
