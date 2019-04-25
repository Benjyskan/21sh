#ifndef LINE_EDITING_H
# define LINE_EDITING_H
# define "history.h"

# define INIT_TXT_SIZE 2 // change to 32(?) later but for debug purpose it's 2
# define BUF_SIZE 4
# define STD_PROMPT "psh $ "

typedef struct				s_st_txt {
	char					*txt;
	size_t					malloc_size;
	size_t					data_size;
	size_t					tracker;
}							t_st_txt;

typedef struct				s_st_prompt {
	char					*prompt;
	size_t					prompt_size;
}							t_st_prompt;

typedef struct				s_st_cmd {
	struct s_txt_struct		st_txt;
	t_pos					start_pos;
	t_pos					relative_pos;
	struct winsize			*window;
	struct s_promt_struct	*st_prompt;
	struct s_hist_lst		*hist_lst;
	struct s_st_cmd			*next;
	struct s_st_cmd			*prev;
}							t_st_cmd;

/*
**	st_txt functions
*/

t_st_txt					*init_st_txt(char *txt);

/*
**	st_prompt functions
*/

t_st_prompt					*init_st_prompt(char *prompt);

#endif
