#include "tosh.h"
#include "reader.h"

void	move_arrow_right(t_st_txt *st_txt)
{
	if (st_txt->tracker < st_txt->data_size)
		st_txt->tracker++;
	else
		ft_putstr_tty(BELL);
}

void	move_arrow_left(t_st_txt *st_txt)
{
	if (st_txt->tracker > 0)
		st_txt->tracker--;
	else
		ft_putstr_tty(BELL);
}

void	go_to_start(t_st_txt *st_txt)
{
	st_txt->tracker = 0;
}

void	go_to_end(t_st_txt *st_txt)
{
	st_txt->tracker = st_txt->data_size;
}
