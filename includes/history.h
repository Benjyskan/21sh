#ifndef HISTORY_H
# define HISTORY_H

# include "reader.h"
# define HIST_FILE "~/.21sh_history"
# define HIST_MAX 600
# define HIST_SIZE 500

typedef struct		s_hist_lst {
	char*				txt;
	struct s_hist_lst *prev;
	struct s_hist_lst *next;
}					t_hist_lst;

t_hist_lst	*get_history(char **env);
int			write_to_history(t_cmd_struct *cmd_struct, char **env);

/*
**	Utils for hist_lst structure : appending, creating, inserting etc...
*/

t_hist_lst	*append_hist_lst(t_hist_lst *hist_lst, char *line);
t_hist_lst	*create_hist_lst(char *line);
void		print_hist_lst(t_hist_lst *hist_lst);
t_hist_lst	*get_end_lst(t_hist_lst *hist_lst);
t_hist_lst	*get_begin_lst(t_hist_lst *hist_lst);

#endif
