#include "tosh.h"
#include "history.h"
#include "lexer.h"
#include "ast.h"

/*
** handle_input
** should pass the inputed cmdline through the lexer to get a token list;
** then create the ast with the token list
** then execute the ast
*/

t_bool	handle_input(t_cmd_struct *cmd_struct, char **env)
{
	t_ast			*ast_root;
	t_token			*token_head;
	int				lexer_ret;

	token_head = NULL;//test
	while ((lexer_ret = lexer(cmd_struct->txt, &token_head, env)) == LEX_CONT_READ)
	{
		//free token list ?

		free_token_list(token_head);
		ft_memdel((void*)&cmd_struct->prompt);
		cmd_struct->prompt = ft_strdup("cont> ");
		//dprintf(g_dev_tty, "OLD_INPUT: {%s}\n", cmd_struct->txt);print_line();
		cmd_struct->append_txt = &cmd_struct->txt[cmd_struct->total_data_size];
		cmd_struct->tracker = 0;
		cmd_struct = input_loop(cmd_struct);
		//dprintf(g_dev_tty, "NEW_INPUT: {%s}\n", cmd_struct->txt);print_line();
	}
	write_to_history(cmd_struct, env);
	if (lexer_ret == LEX_FAIL)
	{
		free_token_list(token_head);
		ft_endl_tty("\x1B[31m""### Lexer FAILED""\x1B[0m");
		return (0);
	}
	else
		ft_endl_tty("\x1B[32m""### lexer SUCCESS""\x1B[0m");
	if (!(ast_root = create_ast(token_head)))
	{
		ft_endl_tty("\x1B[31m""### Parser FAILED""\x1B[0m""\n");
		return (0);
	}
	ft_endl_tty("\x1B[32m""### Parser SUCCESS""\x1B[0m""\n");
	exec_ast(ast_root, env);
	free_ast(ast_root);
	return (1);
}
