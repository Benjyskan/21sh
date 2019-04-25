#ifndef READER_H
# define READER_H

# include "libterm.h"
# include <sys/ioctl.h>
# include "line_editing.h"
# include "history.h"


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

int				input_loop(t_cmd_struct *cmd_struct);

/*
** General display
*/

void			reposition_cursor(t_cmd_struct *cmd_struct);
void			print_prompt(t_cmd_struct *cmd_struct);
void			signal_setup(void);

/*
**	Input string manipulation
*/

size_t			ft_printable_len(const char *str);
void			insert_str(t_cmd_struct *cmd_struct, const char *buf,
		size_t printable_len);


void			clean_exit(int exitno);
/*
**	Functions that have to do with setting up cmd_struct
*/

t_cmd_struct	*get_cmd_struct(t_cmd_struct **new_struct);
void			reset_cmd_struct(t_cmd_struct *cmd_struct);
t_cmd_struct	*init_cmd_struct(char **env);

void			sigint_handler(int signo);
#endif
