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

t_st_cmd	*init_st_cmd(char **env)
{
	t_st_cmd *st_cmd;

	if (!(st_cmd = (t_st_cmd*)malloc(sizeof(*st_cmd))))
		ERROR_MEM;
	st_cmd->st_txt = init_st_txt(NULL);
	st_cmd->prompt = init_st_prompt(NULL);
	retrieve_pos(&st_cmd->start_pos);
	st_cmd->hist_lst = get_history(env);
	st_cmd->hist_lst = insert_right(st_cmd->hist_lst, "", 0); // ? need to malloc "" ?
	get_st_cmd(&st_cmd);
	return (st_cmd);
}
