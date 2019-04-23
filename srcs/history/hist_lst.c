#include "ast.h"
#include "history.h"

t_hist_lst	*create_hist_lst(char *line, char keep)
{
	t_hist_lst	 *res;

	if (!(res = (t_hist_lst*)malloc(sizeof(*res))))
		ERROR_MEM;
	if (!(res->txt = ft_strdup(line)))
		ERROR_MEM;
	if (!(res->cpy = ft_strdup(line)))
		ERROR_MEM;
	res->keep = keep;
	res->prev = NULL;
	res->next = NULL;
	return (res);
}

t_hist_lst	*get_begin_lst(t_hist_lst *hist_lst)
{
	t_hist_lst	*probe;

	probe = hist_lst;
	if (!probe)
		return (NULL);
	else
		while (probe->prev)
			probe = probe->prev;
	return (probe);
}

t_hist_lst	*get_end_lst(t_hist_lst *hist_lst)
{
	t_hist_lst	*probe;

	probe = hist_lst;
	if (!probe)
		return (NULL);
	else
		while (probe->next)
			probe = probe->next;
	return (probe);
}

t_hist_lst	*append_hist_lst(t_hist_lst *hist_lst, char *line, char keep)
{
	t_hist_lst *probe;

	if (!(probe = hist_lst))
	{
		hist_lst = create_hist_lst(line, keep);
		return (hist_lst);
	}
	else
	{
		probe->next = create_hist_lst(line, keep);
		probe->next->prev = probe;
	}
	return (probe->next);
}

void		print_hist_lst(t_hist_lst *hist_lst)
{
	t_hist_lst *probe;

	probe = get_begin_lst(hist_lst);
	ft_printf("--- PRINTING LST --- ");
	print_line();
	while (probe)
	{
		ft_printf("PROBE: TXT: {%s}", probe->txt);
		print_line();
		probe = probe->next;
	}
}
