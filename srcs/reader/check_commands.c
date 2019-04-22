#include "reader.h"

int		check_for_arrows(t_cmd_struct *cmd_struct, char *buf)
{
	if (ft_strncmp(buf, RIGHTARROW, ARROW_LEN + 1) == 0)
		move_arrow_right(cmd_struct);
	else if (ft_strncmp(buf, LEFTARROW, ARROW_LEN + 1) == 0)
		move_arrow_left(cmd_struct);
	else if (ft_strncmp(buf, UPARROW, ARROW_LEN + 1) == 0)
		get_previous_history(cmd_struct);
	else if (ft_strncmp(buf, DOWNARROW, ARROW_LEN + 1) == 0)
		get_previous_history(cmd_struct);
	else if (ft_strncmp(buf, HOME, HOME_LEN + 1) == 0)
		cmd_struct->tracker = 0;
	else if (ft_strncmp(buf, END, END_LEN + 1) == 0)
		cmd_struct->tracker = cmd_struct->current_data_size;
	else
		return (0);
	reposition_cursor(cmd_struct);
	return (1);
}

int		check_for_quit(const char *buf)
{
	if (ft_strncmp(buf, CTRL_D, 2) == 0)
		return (1);
	else
		return (0);
}

int		check_for_signal(const char *buf)
{
	if (ft_strncmp(buf, CTRL_Z, 2) == 0)
	{
		ft_dprintf(2, "SHOULD BE BACKGROUND");
		print_line();
		return (1);
	}
	else if (ft_strncmp(buf, CTRL_C, CTRL_C_LEN) == 0)
	{
		ioctl(g_dev_tty, TIOCSTI, CTRL_C);
		sigint_handler(2);
		return (1);
	}
	return (0);
}

void	shift_chars(char *str, unsigned int shift)
{
	size_t i;

	i = 0;
	while (str[i] && str[i + shift])
	{
		str[i] = str[i + shift];
		i++;
	}
	str[i] = str[i + 1];
}

int		check_for_enter(const char *buf)
{
	if (ft_strncmp(buf, "\r", 2) == 0)
		return (1);
	else
		return (0);
}

int		check_for_delete(t_cmd_struct *cmd_struct, char *buf)
{
	if (ft_strncmp(buf, BACKSPACE, BACKSPACE_LEN + 1) == 0)
	{
		if (cmd_struct->tracker <= 0)
		{
			cmd_struct->tracker = 0;
			ft_putstr_tty(BELL);
			return (1);
		}
		cmd_struct->tracker--;
		cmd_struct->total_data_size -= 1;
		cmd_struct->current_data_size -= 1;
		reposition_cursor(cmd_struct);
		execute_str(ERASE_ENDLINE);
		shift_chars(&cmd_struct->append_txt[cmd_struct->tracker], 1);
		ft_putstr_tty(&cmd_struct->append_txt[cmd_struct->tracker]);
		reposition_cursor(cmd_struct);
		return (1);
	}
	else
		return (0);
}
