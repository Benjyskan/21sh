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
**	Function that scrolls down if need be and write the
**	remainder of the line.
*/

void	move_down(t_st_cmd *st_cmd)
{
	if (st_cmd->start_pos.row + st_cmd->relative_pos.row == st_cmd->window.ws_row)
		update_start_pos(st_cmd);
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
	t_pos		tmp_pos;
	size_t		i;

	st_txt = st_cmd->st_txt;
	i = 0;
	tmp_pos = st_cmd->relative_pos;
	while ((st_txt->tracker + i) < st_txt->data_size && st_txt->txt[st_txt->tracker + i] != '\n')
	{
		write(g_dev_tty, &st_txt->txt[st_txt->tracker + i], 1);
		i++;
		if (tmp_pos.col == st_cmd->window.ws_col)
		{
			move_down(st_cmd); // TODO
			tmp_pos.col = 1;
			tmp_pos.row++;
		}
		else
			tmp_pos.col++;
//		move_cursor(st_cmd->start_pos.col + tmp_pos.col,
//				st_cmd->start_pos.row + tmp_pos.row); // reposiiton
	}
	if (st_txt->txt[st_txt->tracker + i] == '\n' && st_txt->txt[st_txt->tracker + i + 1])
	{
		i++;
		move_down(st_cmd);
		tmp_pos.col = 1;
		tmp_pos.row++;
		return (i);
	}
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
		get_tracker_pos(st_cmd);
		reposition_cursor(st_cmd);
	}
}
