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

void		reposition_cursor(t_cmd_struct *cmd_struct)
{
	int		max_row;
	int		max_col;
	int		current_row;
	int		current_col;
	size_t	prompt_size;

	prompt_size = cmd_struct->prompt ? ft_strlen(cmd_struct->prompt) : 2;
	max_row = cmd_struct->start_pos.row + (prompt_size
			+ cmd_struct->current_data_size) / cmd_struct->window.ws_col;
	max_col = cmd_struct->start_pos.col + (prompt_size
			+ cmd_struct->current_data_size) % cmd_struct->window.ws_col;
	while (max_row > cmd_struct->window.ws_row)
	{
		execute_str(SCROLL_DOWN);
		update_pos(cmd_struct);
		max_row = cmd_struct->start_pos.row + (prompt_size
				+ cmd_struct->current_data_size) / cmd_struct->window.ws_col;
		max_col = cmd_struct->start_pos.col + (prompt_size
				+ cmd_struct->current_data_size) % cmd_struct->window.ws_col;
	}
	current_row = cmd_struct->start_pos.row + (prompt_size
			+ cmd_struct->tracker) / cmd_struct->window.ws_col;
	current_col = cmd_struct->start_pos.col + (prompt_size
			+ cmd_struct->tracker) % cmd_struct->window.ws_col;
	move_cursor(current_col, current_row);
}
