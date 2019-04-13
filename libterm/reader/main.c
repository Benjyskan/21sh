#include "reader.h"

/*void		reposition_cursor(t_pos *saved_pos, size_t append)
{
	check_current_pos;
	check_window_size;
	check_saved_pos;
	if (current_pos.column + append >= window.columns)
		saved_pos->row -= 1; (need to check if it's already 0!)
IMPORTANT : or write char per char ??
//	move_cursor(cmd_struct.start_pos.col, cmd_struct.start_pos.row);
}*/

void	insert_str(t_cmd_line *cmd_struct, char *buf, int ret)
{
	char *tmp;


	if (!(tmp = ft_strdup(&cmd_struct->cmd_line[cmd_struct->position])))
		return ; //ERROR_MEM;
	ft_strcpy(&cmd_struct->cmd_line[cmd_struct->position + ret],
			tmp);
	ft_strncpy(&cmd_struct->cmd_line[cmd_struct->position], buf, ret);
	free(tmp);
}

void	magic_print(char *buf)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		ft_dprintf(2, "%d ", buf[i]);
		i++;
	}
}

char	*input_loop(void)
{
	char	buf[BUF_SIZE + 1];
	t_cmd_line cmd_struct;
	int		ret;

	// need initalization for cmd_struct;
	if (!(cmd_struct.cmd_line = ft_strnew(INIT_CMD_LINE_SIZE)))
		return (NULL); //error
	cmd_struct.current_data_size = 0;
	cmd_struct.current_malloc_size = INIT_CMD_LINE_SIZE;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &cmd_struct.window) == -1)
	{
		ft_dprintf(2, "Error ioctl");//TODO
		return (0);
	}
	cmd_struct.position = 0;

	while ((ret = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	{
		buf[ret] = 0;
		//magic_print(buf);
		cmd_struct.cmd_line = ft_realloc(cmd_struct.cmd_line, cmd_struct.current_data_size, &cmd_struct.current_malloc_size, ret);
		if (check_for_movement(&cmd_struct, buf) || check_for_signal(buf)
		|| check_for_quit(buf) || check_for_delete(&cmd_struct, buf))
			continue ;
		else if (ft_strncmp(buf, "\r", 2) == 0)
			break ;
		else if (ft_strncmp(buf, CTRL_C, 2) == 0)
		{
			*cmd_struct.cmd_line = 0;
			break ;
		}
		else
		{
			if (ret == 1 && *buf == '\x1b') // do we want to be able to put escape codes ?
			{
				*buf = 0;
				continue ;
			}
			insert_str(&cmd_struct, buf, ret);
			execute_str(ERASE_ENDLINE);// should not be necessary if done right
			ft_putstr_tty(&cmd_struct.cmd_line[cmd_struct.position]);
			cmd_struct.current_data_size += ret;
			cmd_struct.position += ret;
			int i;
			i = ft_strlen(&cmd_struct.cmd_line[cmd_struct.position]);
			while (i) // after write, puts cursor back to its previous position doesn't work with \t
			{
				ft_putstr_tty(LEFTARROW);
				i--;
			}
		}
	}
	// ret == 0 ? -1 ?
	return (cmd_struct.cmd_line);
}

void		print_prompt(void)
{
	ft_putstr_tty("$>");
}

int	main(void)
{
	char	*cmd_line;

	if (setup_terminal_settings() == -1)
		return (0);
	while (42)
	{
		print_prompt();
		if (!(cmd_line = input_loop()))
			return (0); //error
		print_line();
	}
	if (reset_terminal_settings())
		return (0);
	else
		return (1);
}
