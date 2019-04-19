#ifndef READER_H
# define READER_H

# include "libterm.h"
# include <sys/ioctl.h>
# define BUF_SIZE 4
# define PROMPT_SIZE
# define INIT_TXT_SIZE 32

typedef struct	s_cmd_struct {
	char				*txt;
	size_t				current_data_size;
	size_t				current_malloc_size;
	t_pos				start_pos;
	struct winsize		window;
	size_t				tracker;
	size_t				nb_lines;
	char				*prompt;
	int					fd;
}				t_cmd_struct;

/*
**	Input checking
*/

int				check_for_arrows(t_cmd_struct *cmd_struct, char *buf);
int				check_for_quit(const char *buf);
int				check_for_enter(const char *buf);
int				check_for_signal(const char *buf);
int				check_for_delete(t_cmd_struct *cmd_struct, char *buf);

/*
**	Arrow movement
*/

void			move_arrow_left(t_cmd_struct *cmd_struct);
void			move_arrow_right(t_cmd_struct *cmd_struct);
void			get_previous_history(t_cmd_struct *cmd_struct);
void			get_next_history(t_cmd_struct *cmd_struct);


/*
** Read input
*/

t_cmd_struct	*input_loop(t_cmd_struct *cmd_struct);

/*
** General display
*/

void			reposition_cursor(t_cmd_struct *cmd_struct);
void			print_prompt(t_cmd_struct *cmd_struct);

/*
**	Input string manipulation
*/

size_t			ft_printable_len(const char *str);
void			insert_str(t_cmd_struct *cmd_struct, const char *buf,
		size_t printable_len);


void			clean_exit(int exitno);
#endif
