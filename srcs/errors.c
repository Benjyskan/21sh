#include "21sh.h"

void	error_mem(void)
{
	ft_putendl_fd("malloc failed", 2);
	exit(EXIT_FAILURE);
}
