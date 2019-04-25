#include "line_editing.h"
#include "ast.h"

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

/*
**	Returns a freshly allocated st_txt with an allocated copy of the txt
**	parameter. If no parameter is passed, duplicates an empty string
*/

t_st_txt	*init_st_txt(char *txt)
{
	t_st_txt	*st_txt;

	if (!(st_txt = (t_st_txt*)malloc(sizeof(*st_txt))))
		ERROR_MEM;
	if (!txt)
	{
		if (!(st_txt->txt = ft_strdup("")))
			ERROR_MEM;
	}
	else
		if (!(st_txt->txt = ft_strdup(txt)))
			ERROR_MEM;

	st_txt->data_size = (size_t)ft_strlen(st_txt->txt);
	st_txt->malloc_size = st_txt->data_size + 1;
	st_txt->tracker = st_txt->data_size;
	return (st_txt);
}

/*
**	Returns a freshly allocated st_prompt with an allocated copy of the prompt
**	parameter. If paramter is empty, duplicates the STD_PROMPT macro.
*/

t_st_prompt	*init_st_prompt(char *prompt)
{
	t_st_prompt	*st_prompt;

	if (!(st_prompt = (t_st_prompt*)malloc(sizeof(*st_prompt))))
		ERROR_MEM;
	if (!prompt)
	{
		if (!(st_prompt->prompt = ft_strdup(STD_PROMPT)))
			ERROR_MEM;
	}
	else
		st_prompt->prompt = ft_strdup(prompt);
	st_prompt->prompt_size = ft_strlen(prompt);
	return (st_prompt);
}
