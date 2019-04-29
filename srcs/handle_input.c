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

t_bool	handle_input(t_st_cmd *st_cmd, char **env)
{
	t_ast			*ast_root;
	t_token			*token_head;
	int				lexer_ret;

	token_head = NULL;
	// need to append all st_cmd's txt
	while ((lexer_ret = lexer(st_cmd->st_txt->txt, &token_head, env)) == LEX_CONT_READ)
	{
		free_token_list(token_head);
		//free st_prompt
		st_cmd = append_st_cmd(st_cmd, "", "cont > ");
	 	input_loop(st_cmd);
	}
	st_cmd->hist_lst = get_end_lst(st_cmd->hist_lst);
	insert_left(st_cmd->hist_lst, st_cmd->st_txt->txt, 1);
	if (lexer_ret == LEX_FAIL)
	{
		free_token_list(token_head);
		ft_endl_tty("\x1B[31m""### Lexer FAILED""\x1B[0m");
		return (0);
	}
/*	else
		ft_endl_tty("\x1B[32m""### lexer SUCCESS""\x1B[0m");*/
	if (!(ast_root = create_ast(token_head)))
	{
		ft_endl_tty("\x1B[31m""### Parser FAILED""\x1B[0m""\n");
		return (0);
	}
//	ft_endl_tty("\x1B[32m""### Parser SUCCESS""\x1B[0m""\n");
	exec_ast(ast_root, env);
	free_ast(ast_root);
	return (1);
}
