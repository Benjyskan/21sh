#include "tosh.h"

char		*my_strtrim(char *str)
{
	int		i;
	char	*tmp;
	char	*res;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] == ' ' || str[i] == '\t')
	{
		i++;
		if (str[i] == 0)
			return (NULL);
	}
	tmp = &str[i];
	i = ft_strlen(tmp) - 1;
	while (tmp[i] == ' ' || tmp[i] == '\t')
		i--;
	res = ft_strndup(tmp, i + 1);
	printf("in strtrim: {%s}, i=%d\n", res, i);
	return (res);
}

/*
** create_cmdlst
** create a new cmdlst
** trim and FREE the cmdline
** return a pointer to the head node
*/

t_cmdlst	*create_cmdlst(char *cmdline)
{
	t_cmdlst	*new_node;

	ft_putendl("Creating new node");
	if (!(new_node = (t_cmdlst*)malloc(sizeof(t_cmdlst))))
		ERROR_MEM;
	if (!(new_node->cmdline = my_strtrim(cmdline)))
		ERROR_MEM;
	ft_memdel((void*)&cmdline);
	new_node->next = NULL;
	return (new_node);
}

/*
** add_to_cmdlst
** append a new node to the list pointed by cmdlst_head
** trim and FREE the cmdline
*/

void		add_to_cmdlst(char *cmdline, t_cmdlst *cmdlst_head)
{
	t_cmdlst	*new_node;
	t_cmdlst	*probe;

	ft_putendl("Adding new node");
	if (!(new_node = (t_cmdlst*)malloc(sizeof(t_cmdlst))))
		ERROR_MEM;
	if (!(new_node->cmdline = my_strtrim(cmdline)))
		ERROR_MEM;
	ft_memdel((void*)&cmdline);
	probe = cmdlst_head;
	while (probe->next)
		probe = probe->next;
	probe->next = new_node;
	new_node->next = NULL;
}

void		print_cmdlst(t_cmdlst *head)//for debug
{
	t_cmdlst	*probe;

	probe = head;
	while (probe->next)
	{
		printf("{%s}\n", probe->cmdline);//TODO
		probe = probe->next;
	}
	printf("{%s}\n", probe->cmdline);
}
