#include "tosh.h"
#include "reader.h"
#include "history.h"

void		update_pos(t_cmd_struct *cmd_struct) // might be useless
{
	cmd_struct->start_pos.row--;
}

/*
**	Function that places the cursor on screen according to the current input
*/

int			get_nb_lines(t_cmd_struct *cmd_struct)
{
	int		nb_lines;
	size_t	prompt_size;

	prompt_size = cmd_struct->prompt ? ft_strlen(cmd_struct->prompt) : 2;
	nb_lines = cmd_struct->start_pos.row + (prompt_size
				+ cmd_struct->current_data_size) / (cmd_struct->window.ws_col + 1);
	return (nb_lines);
}

char		*ft_reverse_strchr(char *string_start, size_t size, char search)
{
	while (size)
	{
		if (string_start[size] == search)
			return (&string_start[size] + 1);
		size--;
	}
	return (string_start);
}

int			need_to_scroll(t_cmd_struct *cmd_struct)
{
	int	last_row;

	last_row = cmd_struct->start_pos.row + get_nb_lines(cmd_struct);
	if (last_row >= cmd_struct->window.ws_row)
		return (1);
	else
		return (0);
}

void		insert_newline(t_cmd_struct *cmd_struct, size_t i)
{
	char *remaining;

	if (need_to_scroll(cmd_struct))
	{
		execute_str(SCROLL_DOWN);
		update_pos(cmd_struct);
	}
	ft_printf("NEWLINE");
	sleep(1);
	execute_str(ERASE_ENDLINE);
	execute_str(CLEAR_BELOW);
	remaining = ft_strchr(&cmd_struct->append_txt[i], '\n');
	write_remaining(remaining);
}

void		write_current_line(t_cmd_struct *cmd_struct)
{
	size_t	i;

	i = cmd_struct->tracker;
	while (cmd_struct->append_txt[i])
	{
 		if (cmd_struct->append_txt[i] == '\n')
			break;
		write(g_dev_tty, &cmd_struct->append_txt[i], 1);
		if ((i + ft_strlen(cmd_struct->prompt)) % (cmd_struct->window.ws_col - 1) == 0)
			insert_newline(cmd_struct, i);
		i++;
	}
}

void		reposition_cursor(t_cmd_struct *cmd_struct)
{
	char	*this_line;
	size_t	line_tracker;
	int		row;
	int		col;

	this_line = ft_reverse_strchr(cmd_struct->append_txt, cmd_struct->tracker, '\n');
	line_tracker = ft_strlen(cmd_struct->prompt) + (&cmd_struct->append_txt[cmd_struct->tracker] - this_line);
	row = cmd_struct->start_pos.row + line_tracker / (cmd_struct->window.ws_col);
	col = line_tracker % (cmd_struct->window.ws_col);
	execute_str(SAVE_CURSOR);
	move_cursor(0, 8);
	ft_printf("COL: %d, ROW: %d ; MAX : COL : %d, ROW: %d TRACKER: %lu\n", col, row, cmd_struct->window.ws_col, cmd_struct->window.ws_row, line_tracker);
	execute_str(RESTORE_CURSOR);
	move_cursor(col, row);
}
