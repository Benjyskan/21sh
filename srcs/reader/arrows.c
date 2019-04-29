#include "tosh.h"
#include "reader.h"

void	get_tracker_pos(t_st_cmd *st_cmd)
{
	size_t i;

	i = 0;
	st_cmd->relative_pos.col = 0;
	st_cmd->relative_pos.row = 0;
	while (i < st_cmd->st_txt->tracker)
	{
		if (st_cmd->st_txt->txt[i] == '\n'
			|| ((st_cmd->st_prompt->size % st_cmd->window.ws_col) + st_cmd->relative_pos.col) == st_cmd->window.ws_col)
		{
			st_cmd->relative_pos.col = 0;
			st_cmd->relative_pos.row++;
		}
		else
			st_cmd->relative_pos.col++;
		i++;
	}
	execute_str(SAVE_CURSOR);
	move_cursor(1, 1);
	ft_printf("Total: %d", st_cmd->st_prompt->size % st_cmd->window.ws_col + st_cmd->relative_pos.col);
	ft_printf("res: %d", st_cmd->window.ws_col);
	execute_str(RESTORE_CURSOR);
}

void	move_arrow_right(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;

	st_txt = st_cmd->st_txt;
	if (st_txt->tracker < st_txt->data_size)
	{
		st_txt->tracker++;
		get_tracker_pos(st_cmd);
	}
	else
		ft_putstr_tty(BELL);
}

void	move_arrow_left(t_st_cmd *st_cmd)
{
	t_st_txt *st_txt;

	st_txt = st_cmd->st_txt;
	if (st_txt->tracker > 0)
	{
		st_txt->tracker--;
		get_tracker_pos(st_cmd);
	}
	else
		ft_putstr_tty(BELL);
}

void	go_to_start(t_st_cmd *st_cmd)
{
	st_cmd->relative_pos.col = 0;
	st_cmd->relative_pos.row = 0; // what happens when prompt bigger than cols
	st_cmd->relative_pos.col += st_cmd->st_prompt->size % st_cmd->window.ws_col;
	st_cmd->st_txt->tracker = 0;
}

void	go_to_end(t_st_cmd *st_cmd)
{
	t_st_txt	*st_txt;

	st_txt = st_cmd->st_txt;
	st_txt->tracker = st_txt->data_size;
	get_tracker_pos(st_cmd);
}
