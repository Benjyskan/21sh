#include "history.h"
#include "tosh.h"
#include "reader.h"
#include "ast.h"
#include "errno.h"
#include "get_next_line.h"

static int		open_history(char **env, int options)
{
	int		fd;
	char	*hist_file;

	if (!(hist_file = ft_strdup(HIST_FILE)))
		ERROR_MEM;
	replace_tilde(&hist_file, env);
	if ((fd = open(hist_file, options, 0640)) == -1)
	{
		//		ft_dprintf(2, "error: failed to open history file");
		return (-1);
	}
	ft_memdel((void*)&hist_file);
	return (fd);
}

t_hist_lst	*get_history(char **env)
{
	t_hist_lst	*hist_lst;
	char		*line;
	size_t		id;
	char		*append_with_newline;
	int			fd;

	if ((fd = open_history(env, O_RDONLY)) < 0)
		return (NULL); //error_msg ?
	line = NULL;
	id = 0;
	hist_lst = NULL;
	while ((get_next_line(fd, &line) > 0) && (ft_strlen(line) > 7))
	{
		ft_printf("---- NEWLINE: %s", &line[6]);
		print_line();
		append_with_newline = ft_strjoin(&line[6], "\n");
		hist_lst = append_hist_lst(hist_lst, append_with_newline, 1);
		ft_memdel((void*)&append_with_newline);
		ft_memdel((void*)&line);
		id++;
	}
	close(fd);
	return (hist_lst);
}

int		write_to_history(t_cmd_struct *cmd_struct, char **env)
{
	t_hist_lst	*hist_lst;
	size_t		id;
	size_t		i;
	int			fd;

	if (!(cmd_struct->hist_lst))
		return (0);
	if ((fd = open_history(env, O_WRONLY | O_CREAT | O_TRUNC)) < 0)
		return (0);
	else
	{
		hist_lst = get_begin_lst(cmd_struct->hist_lst);
		id = 0;
		while (hist_lst)
		{
			if (hist_lst->keep)
			{
				i = 0;
				ft_dprintf(fd, "%4d  ", id);
				while (hist_lst->txt[i])
				{
					write(fd, &hist_lst->txt[i], 1);
					if (hist_lst->txt[i] == '\n' && hist_lst->txt[i + 1] != 0)
					{
						id++;
						ft_dprintf(fd, "%4d  ", id);
					}
					i++;
				}
				id++;
			}
			hist_lst = hist_lst->next;
		}
		close(fd);
		return (1);
	}
}
