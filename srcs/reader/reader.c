#include "tosh.h"
#include "reader.h"
#include "history.h"

size_t	ft_print_len(const char *s1)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (s1[i])
	{
		if (ft_isprint(s1[i]) || s1[i] == '\n')
			res++;
		i++;
	}
	return (res);
}

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

void		update_pos(t_cmd_struct *cmd_struct)
{
	cmd_struct->start_pos.row--;
}

void		reposition_cursor(t_cmd_struct *cmd_struct)
{
	int		max_row;
	int		max_col;
	int		current_row;
	int		current_col;
	size_t	prompt_size;

	prompt_size = cmd_struct->prompt ? ft_strlen(cmd_struct->prompt) : 2;
	max_row = cmd_struct->start_pos.row + (prompt_size + cmd_struct->current_data_size) / cmd_struct->window.ws_col;
	max_col = cmd_struct->start_pos.col + (prompt_size + cmd_struct->current_data_size) % cmd_struct->window.ws_col;
	while (max_row > cmd_struct->window.ws_row)
	{
		execute_str(SCROLL_DOWN);
		update_pos(cmd_struct);
		max_row = cmd_struct->start_pos.row + (prompt_size + cmd_struct->current_data_size) / cmd_struct->window.ws_col;
		max_col = cmd_struct->start_pos.col + (prompt_size + cmd_struct->current_data_size) % cmd_struct->window.ws_col;
	}
	current_row = cmd_struct->start_pos.row + (prompt_size + cmd_struct->tracker) / cmd_struct->window.ws_col;
	current_col = cmd_struct->start_pos.col + (prompt_size + cmd_struct->tracker) % cmd_struct->window.ws_col;
	move_cursor(current_col, current_row);
}

char	*ft_strdup_print(const char *s1)
{
	char	*res;
	size_t	len;
	size_t	i;
	
	i = 0;
	if (!(res = ft_strnew(ft_print_len(s1))))
		return (NULL);
	i = 0;
	len = 0;
	while (s1[i])
	{
		if (ft_isprint(s1[i]))
		{
			res[len] = s1[i];
			len++;
		}
		i++;
	}
	res[i] = 0;
	return (res);
}

void	insert_str(t_cmd_struct *cmd_struct, char *buf, size_t print_len)
{
	char	*tmp;

	if (!(tmp = ft_strdup_print(&cmd_struct->txt[cmd_struct->tracker])))
		return ; //ERROR_MEM;
	ft_strcpy(&cmd_struct->txt[cmd_struct->tracker + print_len],
			tmp);
	ft_strncpy(&cmd_struct->txt[cmd_struct->tracker], buf, print_len);
	free(tmp);
}

void	reset_tracker(t_cmd_struct *cmd_struct)
{
	cmd_struct->tracker = ft_strlen(cmd_struct->txt);
}

t_cmd_struct	*input_loop(t_cmd_struct *cmd_struct)
{
	char	buf[BUF_SIZE + 1];
	int		ret;
	size_t	print_len;

	// need initalization for cmd_struct;
	if (cmd_struct == NULL)
	{
		//need check the arg cmd_struct
		if (!(cmd_struct = (t_cmd_struct*)malloc(sizeof(*cmd_struct))))
			ERROR_MEM;
		if (!(cmd_struct->txt = ft_strnew(INIT_TXT_SIZE)))
			return (NULL); //error
		cmd_struct->current_data_size = 0;
		retrieve_pos(&cmd_struct->start_pos);
		cmd_struct->current_malloc_size = INIT_TXT_SIZE;
		cmd_struct->prompt = ft_strdup("psh");
		if (ioctl(STDIN_FILENO, TIOCGWINSZ, &cmd_struct->window) == -1)
		{
			ft_dprintf(2, "Error ioctl");//TODO
			return (NULL);
		}
		cmd_struct->tracker = 0;
	}
	else
	{
		print_prompt(cmd_struct->prompt);
		ft_bzero(buf, BUF_SIZE + 1);
		while ((ret = read(STDIN_FILENO, buf, BUF_SIZE)) > 0)
		{
			buf[ret] = 0;
			magic_print(buf);
			if (check_for_arrows(cmd_struct, buf) || check_for_signal(buf)
			|| check_for_quit(buf) || check_for_delete(cmd_struct, buf))
				continue ;
			else if ((ft_strncmp(buf, "\r", 2) == 0))
			{
				print_line();
				break ;
			}
			else if (ft_strncmp(buf, CTRL_C, 2) == 0)
			{
				free(cmd_struct->txt);
				return (NULL);
			}
			else if (buf[0] < 0 || buf[0] == '\x1b') // checks for unicode and ANSI
				continue ;
			else
			{
				print_len = ft_print_len(buf);
				cmd_struct->txt = ft_realloc(cmd_struct->txt,
						cmd_struct->current_data_size,
						&cmd_struct->current_malloc_size, ret);
				insert_str(cmd_struct, buf, print_len);
				execute_str(ERASE_ENDLINE);// should not be necessary if done right
				ft_putstr_tty(&cmd_struct->txt[cmd_struct->tracker]);
				cmd_struct->current_data_size += print_len;
				cmd_struct->tracker += print_len;
			}
			reposition_cursor(cmd_struct);
		}
	}
	// ret == 0 ? -1 ?
	//return (ft_strdup(cmd_struct.txt)); // need a speical function that concatenates everything and free everyting here;
	return (cmd_struct);
}
