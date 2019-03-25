#include "tosh.h"

int		tokenise(char *cmdline, char **env)
{
	return (0);
}

int		lexer(t_cmdlst *cmdlst_head, char **env)
{
	t_cmdlst	*probe;

	probe = cmdlst_head;
	while (probe)
	{
		//tokenise(probe->cmdline, env);
		//exec
		probe = probe->next;
	}
	return (1);
}
