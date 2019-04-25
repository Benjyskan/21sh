#include "line_editing.h"
#include "ast.h"

/*
**	Singleton function to set or retrieve st_cmd address
*/

t_st_cmd	*get_st_cmd(t_st_cmd **new_struct)
{
	static t_st_cmd *st_cmd = NULL;

	if (new_struct)
	{
		st_cmd = *new_struct;
		return (NULL);
	}
	else
		return (st_cmd);
}

/*
**	Updates the window struct passed as a parameter by calling the ioctl
**	function. Exits if it fails.
*/

void		update_window_struct(struct winsize *window)
{
	if (ioctl(STDIN_FILENO, TIOCGWINZS, window) == -1)
	{
		ft_dprintf(2, "error ioctl: exiting!");
		clean_exit(1);
	}
}

t_st_cmd	*append_st_cmd(t_st_cmd *st_cmd, const char *txt, const char *prompt)
{
	t_st_cmd	*new;

	if (!(new = (t_st_cmd*)malloc(sizeof(*new))))
		ERROR_MEM;
	new->st_txt = init_st_txt(txt);
	new->prompt = init_st_prompt(prompt);
	retrieve_pos(&new->start_pos);
	new->hist_lst = st_cmd->hist_lst;
	st_cmd->next = new;
	new->prev = st_cmd;
	new->next = NULL;
	return (new);
}

/*
**	Function to initialize st_cmd
*/

t_st_cmd	*init_st_cmd(const char **env)
{
	t_st_cmd *st_cmd;

	if (!(st_cmd = (t_st_cmd*)malloc(sizeof(*st_cmd))))
		ERROR_MEM;
	st_cmd->st_txt = init_st_txt(NULL);
	st_cmd->prompt = init_st_prompt(NULL);
	retrieve_pos(&st_cmd->start_pos);
	st_cmd->hist_lst = get_history(env);
	if (!(st_cmd->window = (struct winsize*)malloc(sizeof(struct winsize))))
		ERROR_MEM;
	update_window_struct(st_cmd->window);
	st_cmd->hist_lst = insert_right(st_cmd->hist_lst, "", 0); // ? need to malloc "" ?
	st_cmd->next = NULL;
	st_cmd->prev = NULL;
	get_st_cmd(&st_cmd);
	return (st_cmd);
}
