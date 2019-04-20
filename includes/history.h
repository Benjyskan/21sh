#ifndef HISTORY_H
# define HISTORY_H
# include "reader.h"

# define HIST_FILE "~/.21sh_history"

int		write_to_history(t_cmd_struct *cmd_struct);
int		open_history(char **env);
#endif
