#include "reader.h"

t_cmd_struct	*get_cmd_struct(t_cmd_struct **new_struct)
{
	static t_cmd_struct *cmd_struct = NULL;

	if (new_struct)
	{
		cmd_struct = *new_struct;
		return (NULL);
	}
	else
		return (cmd_struct);
}
