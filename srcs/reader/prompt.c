#include "libterm.h"
#include "reader.h"

void	print_prompt(t_st_prompt *st_prompt)
{
	ft_putstr_tty(st_prompt->prompt);
}
