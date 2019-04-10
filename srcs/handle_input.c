#include "tosh.h"
#include "lexer.h"
#include "ast.h"

/*
** handle_input
** should pass the inputed cmdline through the lexer to get a token list;
** then create the ast with the token list
** then execute the ast ?
*/

t_bool	handle_input(char *input, char **env)
{
	t_ast			*ast_root;
	t_token			*token_head;

	if (!(token_head = lexer(input, env)))
	{
		printf("\x1B[31m""### Lexer FAILED""\x1B[0m""\n");
		return (0);//check me
	}
	printf("### lexer SUCCESS\n");
	print_token_list(token_head);
	//print_token_list(token_head);
	if (!(ast_root = create_ast(token_head)))
	{
		printf("\x1B[31m""### Parser FAILED""\x1B[0m""\n");
		return (0);
	}
	printf("\x1B[32m""### Parser SUCCESS""\x1B[0m""\n");
	print_ast(ast_root);
	exec_ast(ast_root);
	//exec_ast
	return (1);
}
