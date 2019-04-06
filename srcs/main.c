#include "lexer.h"
#include "ast.h"

int	main(void)
{
	t_token *token_head;
	t_token	*test;

	token_head = NULL;
	add_token_to_list(create_token("ls", 2, TK_WORD), &token_head);
//	system("read -p \"Press enter to continue\"");
	add_token_to_list(create_token("auteur", ft_strlen("auteur"), TK_WORD), &token_head);
	test = create_token("1", 1, TK_WORD);
	add_token_to_list(test, &token_head);
	add_token_to_list(create_token(">", 1, TK_REDIRECTION), &token_head);
	add_token_to_list(create_token("prout", 5, TK_WORD), &token_head);
	printf("--- OUTPUT ---\n");
	parse_pipeline(token_head);
	return (0);
}
