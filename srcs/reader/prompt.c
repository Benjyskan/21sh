#include "libterm.h"
#include "reader.h"

void	print_prompt(t_cmd_struct *cmd_struct)
{
	if (cmd_struct->prompt)
		ft_putstr_tty(cmd_struct->prompt);
	else
	{
		cmd_struct->prompt = ft_strndup("$>", 2);
		ft_putstr_tty(cmd_struct->prompt);
	}
}
