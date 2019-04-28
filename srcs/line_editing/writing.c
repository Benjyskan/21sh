#include "line_editing.h"

/*
**	Function that moves the cursor to the start of the first st_cmd, without
**	using start_pos (useful when window size changes)
*/

void	go_back_to_start(t_st_cmd *st_cmd)
{
	while (st_cmd)
	{
		execute_str(MOVE_UP);
	}
}

/*
**	Function that writes the current line. If a new line is printed, moves down
**	and prints every line and st_cmd following the current line.
*/

void	write_line(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;

	st_txt = st_cmd->st_txt;
	while (tracker < st_txt->data_size && st_txt->txt[st_txt->tracker] != '\n')
	{
		write(g_dev_tty, &st_txt->txt[st_txt->tracker], 1);
		st_txt->tracker++;
		if (st_cmd->current_pos.col == st_cmd->window.ws_col)
		{
			move_down(st_cmd);
			st_cmd->current_pos.col = 0;
			st_cmd->current_pos.row++;
		}
		move_cursor(st_cmd->start_pos.col + st_cmd->current_pos.col,
				st_cmd->start_pos.row + st_cmd->current_pos.row); // reposiiton
	}
	if (st_txt->txt[st_txt->tracker] == '\n')
	{
		st_txt->tracker++;
		move_down(st_cmd);
		st_cmd->current_pos.col = 0;
		st_cmd->current_pos.row++;
	}
	//	write until \n
	//	if end screen  -> evaluate if scroll
	// if scroll : update_pos of all structs
	// else, write everything, updating_pos of following
}
