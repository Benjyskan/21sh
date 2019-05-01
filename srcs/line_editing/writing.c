#include "line_editing.h"

/*
 **	Function that moves the cursor to the start of the first st_cmd, without
 **	using start_pos (useful when window size changes)
 */

void	go_back_to_start(t_st_cmd *st_cmd)
{
	update_window_struct(&st_cmd->window);
	// get number of lines associated with txt (counting \n)
	// move up this number of lines
	// do this with previous st_cmds.
	// go to first column
}

/*
**	Function that writes everything without needing checking for scroll
*/

void	write_no_scroll(t_st_cmd *st_cmd)
{
	size_t		i;
	t_st_txt	*st_txt;

	i = 0;
	st_txt = st_cmd->st_txt;
	while (st_cmd)
	{
		reposition_cursor(st_cmd);
		while (i < st_txt->data_size)
		{
			if (st_txt->txt[i] == '\n')
				;
			else
				write(g_dev_tty, &st_txt->txt[st_txt->tracker + i], 1);
			i++;
		}
		st_cmd = st_cmd->next;
	}
}

void	go_to_newline(st_cmd)
{
}

/*
**	Function that scrolls down if need be and write the
**	remainder of the line.
*/

void	move_down(t_st_cmd *st_cmd)
{
/*	ft_printf("S: %d, R: %d, W: %d", st_cmd->start_pos.row, st_cmd->relative_pos.row, st_cmd->window.ws_row);
	sleep(3);*/
	if (st_cmd->start_pos.row + st_cmd->relative_pos.row >= st_cmd->window.ws_row)
	{
		move_cursor(st_cmd->window.ws_col, st_cmd->window.ws_row);
		execute_str(SCROLL_DOWN);
		update_start_pos(st_cmd);
	}
	return ;
}

/*
 **	Function that writes the current line, starting at tracker. If a new line
 **	is printed, moves down and prints every line and st_cmd following the
 **	current line.
 */

int		write_line(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;
	t_pos		tmp_pos; //legacy ?
	size_t		i;

	st_txt = st_cmd->st_txt;
	i = 0;
	tmp_pos = st_cmd->relative_pos;
	while ((st_txt->tracker + i) < st_txt->data_size && st_txt->txt[st_txt->tracker + i] != '\n')
	{
		write(g_dev_tty, &st_txt->txt[st_txt->tracker + i], 1);
		i++;
		get_pos(st_cmd, st_cmd->st_txt->data_size - 1);
		if ((st_cmd->start_pos.row + st_cmd->relative_pos.row) > st_cmd->window.ws_row
				|| st_cmd->relative_pos.col == st_cmd->window.ws_col - 1)
		{
			move_down(st_cmd); // TODO
			get_pos(st_cmd, st_txt->tracker + i);
			reposition_cursor(st_cmd);
			execute_str(CLEAR_BELOW);
		}
	}
	get_pos(st_cmd, st_cmd->st_txt->tracker);
	if (st_txt->txt[st_txt->tracker + i] == '\n' && st_txt->txt[st_txt->tracker + i + 1])
	{
		i++;
		move_down(st_cmd);
		tmp_pos.col = 1;
		tmp_pos.row++;
		return (i);
	}
	execute_str(ERASE_ENDLINE);
	return (0);
	//	write until \n
	//	if end screen  -> evaluate if scroll
	// if scroll : update_pos of all structs
	// else, write everything, updating_pos of following
}

/*
 **	Function that writes every line in the st_cmd, starting form
 **	tracker
 */

void		write_st_cmd(t_st_cmd *st_cmd)
{
	size_t	step;

	while ((step = write_line(st_cmd)))
	{
		st_cmd->st_txt->tracker += step;
		get_pos(st_cmd, st_cmd->st_txt->tracker);
		reposition_cursor(st_cmd);
	}
}
