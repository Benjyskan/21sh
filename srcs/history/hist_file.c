#include "history.h"
#include "reader.h"
#include "ast.h"

int		open_history(void)
{
	int fd;

	if ((fd = open(HIST_FILE, O_RDWR | O_APPEND | O_CREAT, 0640)) == -1)
	{
		ft_dprintf(2, "error: failed to open history file");
		return (-1);
	}
	return (fd);
}

int		write_to_history(t_cmd_struct *cmd_struct)
{
	int fd;

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
