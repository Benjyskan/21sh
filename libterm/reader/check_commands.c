#include "reader.h"

int		check_for_movement(t_cmd_line *cmd_struct, char *buf)
{
	int	i;
	if (ft_strncmp(buf, RIGHTARROW, ARROW_LEN + 1) == 0)
	{
		if (cmd_struct->position < cmd_struct->current_data_size)
		{
			if (cmd_struct->cmd_line[cmd_struct->position] == '\t')
			{
				i = 0;
				while (i < 4)
				{
					ft_putstr_tty(RIGHTARROW);
					i++;
				}
			}
			else
				ft_putstr_tty(RIGHTARROW);
			cmd_struct->position += 1;
		}
	}
	else if (ft_strncmp(buf, LEFTARROW, ARROW_LEN + 1) == 0)
	{
		move_arrow_left(cmd_struct);
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

void	shift_chars(char *str)
{
	size_t i;

	i = 0;
	while (str[i] && str[i + 1])
	{
		str[i] = str[i + 1];
		i++;
	}
	str[i] = str[i + 1];
}

int		check_for_delete(t_cmd_line *cmd_struct, char *buf)
{
	if (ft_strncmp(buf, BACKSPACE, BACKSPACE_LEN + 1) == 0)
	{
		if (cmd_struct->position == 0)
			return (1);
		shift_chars(&cmd_struct->cmd_line[cmd_struct->position - 1]);
		move_arrow_left(cmd_struct);
		execute_str(ERASE_ENDLINE);
//		ft_dprintf(2, "{%s}", &cmd_struct->cmd_line[cmd_struct->position]);
		execute_str(SAVE_CURSOR);
		ft_putstr_tty(&cmd_struct->cmd_line[cmd_struct->position]);
		execute_str(RESTORE_CURSOR);
//		cmd_struct->position -= 1;
		cmd_struct->current_data_size -= 1;
		return (1);
	}
	else
		return (0);
}
