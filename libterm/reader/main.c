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

/*void	insert_str(t_cmd_line *cmd_struct, char *buf, int ret)
{
	char *tmp;


	if (!(tmp = ft_strdup(&cmd_struct->cmd_line[cmd_struct->position])))
		return ; //ERROR_MEM;
	ft_strcpy(&cmd_struct->cmd_line[cmd_struct->position + ret],
			tmp);
	ft_strncpy(&cmd_struct->cmd_line[cmd_struct->position], buf, ret);
	free(tmp);
}*/

int		compare_pos(t_pos *pos_a, t_pos *pos_b)
{
	if (pos_a->col == pos_b->col)
		return (pos_a->row - pos_b->row);
	else
		return (pos_a->col - pos_b->col);
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
	char	c;
	int		ret;
	t_pos	old_pos;
	t_pos	new_pos;
	t_input		input;

	// need initalization for input;
	retrieve_pos(&input.start_pos);
	retrieve_pos(&old_pos);
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &input.window) == -1)
	{
		ft_dprintf(2, "Error ioctl");//TODO
		return (0);
	}
	ft_bzero(buf, BUF_SIZE);
	while ((ret = read(STDIN_FILENO, &c, 1)) > 0)
	{
		ft_strncat(buf, &c, 1);
		//magic_print(buf);
		if (check_for_movement(&input, buf) || check_for_signal(buf)
		|| check_for_quit(buf) || check_for_delete(&input, buf))
		{
			ft_bzero(buf, BUF_SIZE);
			continue ;
		}
		else if (ft_strncmp(buf, "\r", 2) == 0)
		{
			ft_bzero(buf, BUF_SIZE);
			break ;
		}
		else if (ft_strncmp(buf, CTRL_C, 2) == 0)
			clean_exit(0);//1 ?
		else
		{
			ft_putchar_tty(c);
			retrieve_pos(&new_pos);
			if (compare_pos(&old_pos, &new_pos))
			{
				old_pos = new_pos;
				ft_bzero(buf, BUF_SIZE);
			}
		}
	}
	// ret == 0 ? -1 ?
	return (NULL);
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
