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

void			error_read(void)
{
	ft_dprintf(2, "error: failed to read. Exiting");
	print_line();
	clean_exit(1);
}

void			write_buf(t_cmd_struct *cmd_struct, char *buf)
{
	size_t printable_len;
	size_t diff_size;

	printable_len = ft_printable_len(buf);
	diff_size = cmd_struct->append_txt - cmd_struct->txt;
	cmd_struct->txt = ft_realloc(cmd_struct->txt,
			cmd_struct->total_data_size,
			&cmd_struct->total_malloc_size, printable_len + 1);
	get_cmd_struct(&cmd_struct);
	cmd_struct->append_txt = cmd_struct->txt + diff_size;
	insert_str(cmd_struct, buf, printable_len);
	ft_putstr_tty(&cmd_struct->append_txt[cmd_struct->tracker]);
	cmd_struct->current_data_size += printable_len;
	cmd_struct->total_data_size += printable_len;
	cmd_struct->tracker += printable_len;
}

t_cmd_struct	*input_loop(t_cmd_struct *cmd_struct)
{
	char	buf[BUF_SIZE + 1];
	int		ret;

	cmd_struct->current_data_size = 0;
	cmd_struct->tracker = 0;
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
		{
			buf[0] = '\n';
			buf[1] = 0;
			write_buf(cmd_struct, buf);
			break ;
		}
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
