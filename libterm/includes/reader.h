#ifndef READER_H
# define READER_H

# include "libterm.h"
# include <sys/ioctl.h>
# define BUF_SIZE 8
# define INIT_CMD_LINE_SIZE 32
# define CTRL_Z "\x1a"
# define CTRL_D "\x04"
# define CTRL_C "\x03"

typedef struct	s_input {
	t_pos			start_pos;
	struct winsize	window;
	struct t_line	**line;
}				t_input;

typedef struct	s_line {
	char			*data;
	int				disp_size;
	int				selected;
	struct s_line	*next;
	struct s_line	*prev;
}				t_line;

/*
**	Input checking
*/

int		check_for_movement(t_input *input, char *buf);
int		check_for_quit(char *buf);
int		check_for_signal(char *buf);
int		check_for_delete(t_input *input, char *buf);

/*
**	Arrow movement
*/

//void	move_arrow_left(t_cmd_line *cmd_struct);

void	clean_exit(int exitno);
#endif
