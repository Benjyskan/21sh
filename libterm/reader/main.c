#include "reader.h"

size_t	ft_print_len(const char *s1)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (s1[i])
	{
		if (ft_isprint(s1[i]))
			res++;
		i++;
	}
	return (res);
}

void	magic_print(char *buf)
{
	int	i;

	i = 0;
	execute_str(SAVE_CURSOR);
	move_cursor(0, 0);
	while (i < BUF_SIZE + 1)
	{
		ft_dprintf(2, "%-3d ", buf[i]);
		i++;
	}
	execute_str(RESTORE_CURSOR);
}

void		update_pos(t_cmd_struct *cmd_struct)
{
	cmd_struct->start_pos.row--;
}

void		reposition_cursor(t_cmd_struct *cmd_struct)
{
	int	row;
	int	col;

	row = cmd_struct->start_pos.row + (2 + cmd_struct->tracker) / cmd_struct->window.ws_col;
	col = cmd_struct->start_pos.col + (2 + cmd_struct->tracker) % cmd_struct->window.ws_col;
	while (row > cmd_struct->window.ws_row)
	{
		execute_str(SCROLL_DOWN);
		update_pos(cmd_struct);
		row = cmd_struct->start_pos.row + (2 + cmd_struct->tracker) / cmd_struct->window.ws_col;
		col = cmd_struct->start_pos.col + (2 + cmd_struct->tracker) % cmd_struct->window.ws_col;
	}
	move_cursor(col, row);
}

char	*ft_strdup_print(const char *s1)
{
	char	*res;
	size_t	len;
	size_t	i;
	
	i = 0;
	if (!(res = ft_strnew(ft_print_len(s1))))
		return (NULL);
	i = 0;
	len = 0;
	while (s1[i])
	{
		if (ft_isprint(s1[i]))
		{
			res[len] = s1[i];
			len++;
		}
		i++;
	}
	return (res);
}

void	insert_str(t_cmd_struct *cmd_struct, char *buf, size_t print_len)
{
	char	*tmp;

	if (!(tmp = ft_strdup_print(&cmd_struct->txt[cmd_struct->tracker])))
		return ; //ERROR_MEM;
	ft_strcpy(&cmd_struct->txt[cmd_struct->tracker + print_len],
			tmp);
	ft_strncpy(&cmd_struct->txt[cmd_struct->tracker], buf, print_len);
	free(tmp);
}


void		print_prompt(void)
{
	ft_putstr_tty("$>");
}

char	*input_loop(void)
{
	char	buf[BUF_SIZE + 1];
	t_cmd_struct cmd_struct;
	int		ret;
	size_t	print_len;

	// need initalization for cmd_struct;
	if (!(cmd_struct.txt = ft_strnew(INIT_TXT_SIZE)))
		return (NULL); //error
	cmd_struct.current_data_size = 0;
	retrieve_pos(&cmd_struct.start_pos);
	cmd_struct.current_malloc_size = INIT_TXT_SIZE;
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &cmd_struct.window) == -1)
	{
		ft_dprintf(2, "Error ioctl");//TODO
		return (0);
	}
	cmd_struct.tracker = 0;
	print_prompt();

	ft_bzero(buf, BUF_SIZE + 1);
	while ((ret = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	{
		buf[ret] = 0;
		magic_print(buf);
		if (check_for_arrows(&cmd_struct, buf) || check_for_signal(buf)
		|| check_for_quit(buf) || check_for_delete(&cmd_struct, buf))
			continue ;
		else if ((ft_strncmp(buf, "\r", 2) == 0) || ft_strncmp(buf, "\t", 2) == 0 || ft_strncmp(buf, "\x0b", 2) == 0)
			break ;
		else if (ft_strncmp(buf, CTRL_C, 2) == 0)
		{
			free(cmd_struct.txt);
			cmd_struct.txt = NULL;
			break ;
		}
		else if (buf[0] < 0 || buf[0] == '\x1b') // checks for unicode and ANSI
			continue ;
		else
		{
			print_len = ft_print_len(buf);
			cmd_struct.txt = ft_realloc(cmd_struct.txt,
					cmd_struct.current_data_size,
					&cmd_struct.current_malloc_size, ret);
			insert_str(&cmd_struct, buf, print_len);
			execute_str(ERASE_ENDLINE);// should not be necessary if done right
			ft_putstr_tty(&cmd_struct.txt[cmd_struct.tracker]);
			cmd_struct.current_data_size += print_len;
			cmd_struct.tracker += print_len;
		}
		reposition_cursor(&cmd_struct);
	}
	// ret == 0 ? -1 ?
	return (cmd_struct.txt); // need a speical function that concatenates everything and free everyting here;
}


int	main(void)
{
	char	*txt;

	if (setup_terminal_settings() == -1)
		return (0);
	while (42)
	{
		if (!(txt = input_loop()))
			break ; //error
		print_line();
	}
	if (reset_terminal_settings())
		return (0);
	else
		return (1);
}
