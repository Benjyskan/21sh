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

t_cmd_struct	*init_cmd_struct(char **env)
{
	t_cmd_struct *cmd_struct;

	if (!(cmd_struct = (t_cmd_struct*)malloc(sizeof(*cmd_struct))))
		ERROR_MEM;
	if (!(cmd_struct->txt = ft_strnew(INIT_TXT_SIZE)))
		return (NULL); //error
	cmd_struct->current_data_size = 0;
	cmd_struct->fd = open_history(env);
	retrieve_pos(&cmd_struct->start_pos);
	cmd_struct->current_malloc_size = INIT_TXT_SIZE;
	cmd_struct->prompt = ft_strdup("psh $ ");
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &cmd_struct->window) == -1)
	{
		ft_dprintf(2, "error ioctl : exiting!");//TODO
		clean_exit(1);
	}
	cmd_struct->tracker = 0;
	return (cmd_struct);
}

void			error_read(void)
{
	ft_dprintf(2, "error: failed to read. Exiting");
	print_line();
	clean_exit(1);
}

void			write_buf(t_cmd_struct *cmd_struct, char *buf)
{
	size_t printable_len;

	printable_len = ft_printable_len(buf);
	cmd_struct->txt = ft_realloc(cmd_struct->txt,
			cmd_struct->current_data_size,
			&cmd_struct->current_malloc_size, printable_len + 1);
	insert_str(cmd_struct, buf, printable_len);
	execute_str(ERASE_ENDLINE);// should not be necessary if done right
	ft_putstr_tty(&cmd_struct->txt[cmd_struct->tracker]);
	cmd_struct->current_data_size += printable_len;
	cmd_struct->tracker += printable_len;
}

t_cmd_struct	*input_loop(t_cmd_struct *cmd_struct, char **env)
{
	char	buf[BUF_SIZE + 1];
	int		ret;

	if (cmd_struct == NULL)
		cmd_struct = init_cmd_struct(env);
	retrieve_pos(&cmd_struct->start_pos);
	print_prompt(cmd_struct);
	ft_bzero(buf, BUF_SIZE + 1);
	while ((ret = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
	{
		magic_print(buf);
		buf[ret] = 0;
		if (check_for_arrows(cmd_struct, buf) || check_for_signal(buf)
				|| check_for_quit(buf) || check_for_delete(cmd_struct, buf))
			continue ;
		else if (check_for_enter(buf))
			break ;
		else if (buf[0] < 0 || buf[0] == '\x1b') // checks for unicode and ANSI
			continue ;
		else
			write_buf(cmd_struct, buf);
		reposition_cursor(cmd_struct);
	}
	if (ret == -1)
		error_read();
	return (cmd_struct);
}
