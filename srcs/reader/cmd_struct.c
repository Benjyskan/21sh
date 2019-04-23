#include "ast.h"
#include "history.h"
#include "reader.h"

/*
**	Singleton function to set or retrieve cmd_struct address
*/

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

/*
**	Function to reset the cmd_struct without freeing it. Does not reset
**	everything, but only what needs to be reset to continue reading without
**	losing the initial text.
*/

void		reset_cmd_struct(t_cmd_struct *cmd_struct) //only modifies loal copy ?
{
	ft_bzero(cmd_struct->txt, cmd_struct->total_data_size);
	cmd_struct->total_data_size = 0;
	cmd_struct->tracker = 0;
	cmd_struct->current_data_size = 0;
	retrieve_pos(&cmd_struct->start_pos);
	ft_memdel((void*)&cmd_struct->prompt);
	if (!(cmd_struct->prompt = ft_strdup("psh $ "))) //protect //define PROMPT ?
		ERROR_MEM;
	cmd_struct->append_txt = cmd_struct->txt;
}

/*
**	Function to initialize cmd_struct
*/

t_cmd_struct	*init_cmd_struct(char **env)
{
	t_cmd_struct *cmd_struct;

	if (!(cmd_struct = (t_cmd_struct*)malloc(sizeof(*cmd_struct))))
		ERROR_MEM;
	if (!(cmd_struct->txt = ft_strnew(INIT_TXT_SIZE)))
		return (NULL); //ERROR_MEM;
	cmd_struct->total_data_size = 0;
	retrieve_pos(&cmd_struct->start_pos);
	cmd_struct->total_malloc_size = INIT_TXT_SIZE;
	if (!(cmd_struct->prompt = ft_strdup("psh $ ")))// protect //define PROMPT ?
		ERROR_MEM;
	cmd_struct->append_txt = cmd_struct->txt;
	cmd_struct->hist_lst = get_history(env);
	cmd_struct->hist_lst = insert_right(cmd_struct->hist_lst, "", 0);
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &cmd_struct->window) == -1)
	{
		ft_dprintf(2, "error ioctl : exiting!");//TODO
		clean_exit(1);
	}
	get_cmd_struct(&cmd_struct);
	return (cmd_struct);
}

