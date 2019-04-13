#ifndef READER_H
# define READER_H

# include "libterm.h"
# include <sys/ioctl.h>
# define BUF_SIZE 8
# define INIT_CMD_LINE_SIZE 32
# define CTRL_Z "\x1a"
# define CTRL_D "\x04"
# define CTRL_C "\x03"

typedef struct	s_cmd_line {
	char			*cmd_line;
	size_t			current_data_size;
	size_t			current_malloc_size;
	t_pos			start_pos;
	struct winsize	window;
	size_t			position;
	size_t			nb_lines;
}				t_cmd_line;

/*
**	Input checking
*/

int		check_for_movement(t_cmd_line *cmd_struct, char *buf);
int		check_for_quit(char *buf);
int		check_for_signal(char *buf);
int		check_for_delete(t_cmd_line *cmd_struct, char *buf);

/*
**	Arrow movement
*/

void	move_arrow_left(t_cmd_line *cmd_struct);

void	clean_exit(int exitno);
#endif
