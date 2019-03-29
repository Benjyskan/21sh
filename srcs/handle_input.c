#include "tosh.h"

/*
** handle_input
** should pass the inputed cmdline through the lexer to get a token list;
** then ..
*/

t_bool	handle_input(char *input, char **env)
{
	t_tklst			*tklst_head;

	if (!(tklst_head = lexer(input, env)))
	{
		printf("### lexer FAILED\n");
		return (0);//check me
	}
	//parser >> Tree
	printf("### lexer SUCCESS\n");
	print_token_list(tklst_head);
	return (1);
}
