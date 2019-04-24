#include "tosh.h"
#include "history.h"
#include "lexer.h"
#include "ast.h"

/*
** handle_input
** 1. get token_list from input
** 2. store input to history
** 3. get ast from token_list
** 4. execute ast
** 5. free ast
*/

t_hist_lst	*get_keep(t_hist_lst *hist_lst)
{
	t_hist_lst *probe;

	if (!(probe = hist_lst))
		return (NULL);
	while (probe->keep)
		probe = probe->next;
	return (probe);
}

t_hist_lst		*insert_left(t_hist_lst *hist_lst, char *line, char keep)
{
	t_hist_lst	*probe;
	t_hist_lst	*insert;

	insert = create_hist_lst(line, keep);
	if (!(probe = hist_lst))
		return (insert);
	else
	{
		if (probe->prev)
		{
			probe->prev->next = insert;
			insert->prev = probe->prev;
		}
		insert->next = probe;
		probe->prev = insert;
	}
	return (insert);
} // should no be in handle_input !

t_bool	handle_input(t_cmd_struct *cmd_struct, char **env)
{
	t_ast			*ast_root;
	t_token			*token_head;
	int				lexer_ret;

	token_head = NULL;
	while ((lexer_ret = lexer(cmd_struct->txt, &token_head, env)) == LEX_CONT_READ)
	{
		free_token_list(token_head);
		ft_memdel((void*)&cmd_struct->prompt);
		if (!(cmd_struct->prompt = ft_strdup("cont> ")))//define PROMPT_CONT ?
			ERROR_MEM;
		cmd_struct->append_txt = &cmd_struct->txt[cmd_struct->total_data_size];
		cmd_struct->tracker = 0;
	 	input_loop(cmd_struct);
	}
	cmd_struct->hist_lst = get_end_lst(cmd_struct->hist_lst);
	insert_left(cmd_struct->hist_lst, cmd_struct->txt, 1);
	if (lexer_ret == LEX_FAIL)
	{
		free_token_list(token_head);
		ft_endl_tty("\x1B[31m""### Lexer FAILED""\x1B[0m");
		return (0);
	}
	else
//		ft_endl_tty("\x1B[32m""### lexer SUCCESS""\x1B[0m");
	if (!(ast_root = create_ast(token_head)))
	{
		ft_endl_tty("\x1B[31m""### Parser FAILED""\x1B[0m""\n");
		return (0);
	}
	//ft_endl_tty("\x1B[32m""### Parser SUCCESS""\x1B[0m""\n");
	exec_ast(ast_root, env);
	free_ast(ast_root);
	return (1);
}
