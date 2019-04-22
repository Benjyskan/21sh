#include "history.h"
#include "tosh.h"
#include "reader.h"
#include "ast.h"
#include "errno.h"
#include "get_next_line.h"

static int		open_history(char **env)
{
	int		fd;
	char	*hist_file;

	hist_file = ft_strdup(HIST_FILE);
	replace_tilde(&hist_file, env);
	if ((fd = open(hist_file, O_RDWR | O_APPEND | O_CREAT, 0640)) == -1)
	{
		ft_dprintf(2, "error: failed to open history file");
		return (-1);
	}
	ft_memdel((void*)&hist_file);
	return (fd);
}

t_hist_lst	*get_history(char **env)
{
//	t_hist_lst	*hist_lst;
	char		*line;
	int fd;


	if ((fd = open_history(env)) < 0)
		return (NULL); //error_msg ?
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		// fill history
		ft_memdel((void*)&line);
	}
	close(fd);
	return (NULL);
}

int		write_to_history(t_cmd_struct *cmd_struct, char **env)
{
	static int fd = -2;

	if (is_full_of_whitespaces(cmd_struct->txt))
		return (0);
	if (fd == -2)
		fd = open_history(env);
	if (fd < 0)
		return (0);
	else
	{
		//get_cmd_number ? (not line number!)
		ft_dprintf(fd, "\"%s\"\n", cmd_struct->txt);
		return (1);
	}
}
