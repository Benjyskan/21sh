#include "21sh.h"

void	free_cmdlst(t_cmdlst *cmdlst_head)
{
	t_cmdlst	*probe;
	t_cmdlst	*prev;

	probe = cmdlst_head;
	prev = cmdlst_head;
	while (probe->next)
	{
		ft_memdel((void*)&probe->cmdline);
		probe = probe->next;
		ft_memdel((void*)&prev);
		prev = probe;
	}
	ft_memdel((void*)&probe->cmdline);
	ft_memdel((void*)&prev);
}
