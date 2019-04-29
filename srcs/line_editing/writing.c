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
**	Function that prints a newline, scrolls down if need be and write the
**	remainder of the line.
*/

void	move_down(t_st_cmd *st_cmd)
{
	(void)st_cmd;
	return ;
}

/*
**	Function that writes the current line, starting at tracker. If a new line
**	is printed, moves down and prints every line and st_cmd following the
**	current line.
*/

void	write_line(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;

	st_txt = st_cmd->st_txt;
	while (st_txt->tracker < st_txt->data_size && st_txt->txt[st_txt->tracker] != '\n')
	{
		write(g_dev_tty, &st_txt->txt[st_txt->tracker], 1);
		st_txt->tracker++;
		if (st_cmd->relative_pos.col == st_cmd->window.ws_col)
		{
			move_down(st_cmd); // TODO
			st_cmd->relative_pos.col = 0;
			st_cmd->relative_pos.row++;
		}
		else
			st_cmd->relative_pos.col++;
//		move_cursor(st_cmd->start_pos.col + st_cmd->relative_pos.col,
//				st_cmd->start_pos.row + st_cmd->relative_pos.row); // reposiiton
	}
	if (st_txt->txt[st_txt->tracker] == '\n')
	{
		st_txt->tracker++;
		move_down(st_cmd);
		st_cmd->relative_pos.col = 0;
		st_cmd->relative_pos.row++;
	}
	//	write until \n
	//	if end screen  -> evaluate if scroll
	// if scroll : update_pos of all structs
	// else, write everything, updating_pos of following
}
