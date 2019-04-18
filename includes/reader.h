#ifndef READER_H
# define READER_H

# include "libterm.h"
# include <sys/ioctl.h>
# define BUF_SIZE 4
# define PROMPT_SIZE
# define INIT_TXT_SIZE 32
# define CTRL_Z "\x1a"
# define CTRL_D "\x04"
# define CTRL_C "\x03"

typedef struct	s_cmd_struct {
	char				*txt;
	size_t				current_data_size;
	size_t				current_malloc_size;
	t_pos				start_pos;
	struct winsize		window;
	size_t				tracker;
	size_t				nb_lines;
	char				*prompt;
	struct s_cmd_struct	*next;
}				t_cmd_struct;

/*
**	Input checking
*/

int		check_for_arrows(t_cmd_struct *cmd_struct, char *buf);
int		check_for_quit(char *buf);
int		check_for_signal(char *buf);
int		check_for_delete(t_cmd_struct *cmd_struct, char *buf);

/*
**	Arrow movement
*/

void	move_arrow_left(t_cmd_struct *cmd_struct);
void	reposition_cursor(t_cmd_struct *cmd_struct);

void	clean_exit(int exitno);

/*
** reader
*/

t_cmd_struct	*input_loop(t_cmd_struct *cmd_struct);
void			reposition_cursor(t_cmd_struct *cmd_struct);

/*
** prompt.c
*/

void				print_prompt(char *prompt_str);
#endif
