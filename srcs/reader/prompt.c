#include "libterm.h"

void	print_prompt(char *prompt_str)
{
	ft_putstr_tty(prompt_str ? prompt_str : "NULL");
	ft_putstr_tty("> ");
}
