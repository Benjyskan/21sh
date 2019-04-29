#include "reader.h"
#include "tosh.h"
#include "history.h"

void	magic_print(char *buf)
{
	int	i;

	i = 0;
	execute_str(SAVE_CURSOR);
	move_cursor(0, 0);
	while (i < BUF_SIZE + 1)
	{
		ft_dprintf(2, "%-3d ", buf[i]);
		i++;
	}
	execute_str(RESTORE_CURSOR);
}

/*
**	Appends some text at the end of the current st_txt
*/

void	append_txt(t_st_cmd *st_cmd, const char *buf)
{
	t_st_txt	*st_txt;
	size_t		buf_len;

	buf_len = ft_strlen(buf);
	st_txt = st_cmd->st_txt;
	st_txt->txt = ft_realloc(st_txt->txt, st_txt->data_size,
			&st_txt->malloc_size, buf_len);
	ft_strncat(&st_txt->txt[st_txt->data_size], buf, buf_len);
	st_txt->data_size += buf_len;
	write_line(st_cmd);
}

/*
**	Assumes we are at the beginning of a line, with a freshly initalized st_cmd.
**	Reads stdin, breaks when \n is entered, returning the filled st_cmd.
*/

int		input_loop(t_st_cmd *st_cmd)
{
	char	buf[BUF_SIZE + 1];
	int		ret;

	ft_bzero(buf, BUF_SIZE + 1);
	print_prompt(st_cmd->st_prompt);
	retrieve_pos(&st_cmd->start_pos);
	while ((ret = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	{
//		magic_print(buf);
		buf[ret] = 0;
		if (check_for_arrows(st_cmd, buf) || check_for_signal(buf)
			|| check_for_delete(st_cmd, buf))
			continue ;
		else if (check_for_enter(buf))
		{
			ft_strncpy(buf, "\n", 1);
			append_txt(st_cmd, (const char*)buf);
			break ;
		}
		else if (check_for_quit(buf))
			return (0);
		else if (buf[0] < 0 || buf[0] == '\x1b') // checks for unicode and ANSI
			continue ;
		else
			append_txt(st_cmd, (const char*)buf);
		reposition_cursor(st_cmd);
	}
	if (ret > 0)
		return (1);
	return (0);
}
