#include "tosh.h"
#include "lexer.h"
#include "ast.h"

/*
** handle_input
** should pass the inputed cmdline through the lexer to get a token list;
** then ..
*/

t_bool	handle_input(char *input, char **env)
{
	//t_tklst			*tklst_head;
	t_ast			*ast_head;
	//
	t_token			*token_head;

	//if (!(tklst_head = lexer(input, env)))
	if (!(token_head = lexer(input, env)))
	{
		printf("### lexer FAILED\n");
		return (0);//check me
	}
	//parser >> Tree
	printf("### lexer SUCCESS\n");
	print_token_list(token_head);
	if (!(ast_head = token_parser(token_head)))
	{
		printf("### Parsing FAILED\n");
		return (0);
	}
	printf("### Parsing SUCCESS\n");
	return (1);
}
