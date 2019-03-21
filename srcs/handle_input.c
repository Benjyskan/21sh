#include "tosh.h"

/*
** split_on_colomn
** create a new cmdlst by spliting the input on ';'
** return the head of the list
*/

static t_cmdlst	*split_on_colomn(char *input, char **env)//TODO bad name
{
	char		**tmp_tab;
	t_cmdlst	*cmdlst_head;
	int			i;

	(void)env;
	if (!(tmp_tab = my_strsplit(input)))
		ERROR_MEM;
	if (!*tmp_tab)
	{
		ft_putendl("CHECK111");//when do this happen ?
		ft_memdel((void*)&tmp_tab);
		return (NULL);
	}
	if (!(cmdlst_head = create_cmdlst(tmp_tab[0])))
		ERROR_MEM;
	i = 0;
	while (tmp_tab[++i])
		add_to_cmdlst(tmp_tab[i], cmdlst_head);//no need to protect
	ft_memdel((void*)&tmp_tab);
	return (cmdlst_head);
}

void			handle_input(char *input, char **env)
{
	t_cmdlst	*cmdlst_head;
	
	if (!(cmdlst_head = split_on_colomn(input, env)))
		return ;
	print_cmdlst(cmdlst_head);//debug
	ft_memdel((void*)&input);
	//FOR EACH CMD
	//expand var (plus tard)
	//tokenize
	//lexer
	//exec tree

	my_pipe(cmdlst_head->cmdline);//test

	free_cmdlst(cmdlst_head);
}
