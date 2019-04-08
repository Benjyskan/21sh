#include "lexer.h"
#include "ast.h"

int	main(void)
{
	t_token *token_head;

	token_head = NULL;
	add_token_to_list(create_token("l", 1, TK_WORD), &token_head);
	add_token_to_list(create_token("'s'", 3, TK_SQ_STR), &token_head);
	add_token_to_list(create_token(" ", 1, TK_EAT), &token_head);
//	system("read -p \"Press enter to continue\"");
	print_token_list(token_head);
	printf("--- OUTPUT ---\n");
	parse_pipeline(token_head);
	return (0);
}
