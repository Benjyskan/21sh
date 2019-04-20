#include "history.h"
#include "tosh.h"
#include "reader.h"
#include "ast.h"
#include "errno.h"

int		open_history(char **env)
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

int		write_to_history(t_cmd_struct *cmd_struct)
{
	int fd;

	if (is_full_of_whitespaces(cmd_struct->txt))
		return (0);
	fd = cmd_struct->fd;
	if (fd < 0)
		return (0);
	else
	{

		//get_cmd_number ? (not line number!)
		ft_dprintf(fd, "\"%s\"\n", cmd_struct->txt);
		return (1);
	}
}
