#include "lexer.h"
#include "ast.h"

int	main(void)
{
	t_tklst *tklst;;
	t_token	*test;

	tklst = NULL;
	add_token_to_tklst(create_token("ls", 2, TK_LITERAL), &tklst);
	add_token_to_tklst(create_token("auteur", ft_strlen("auteur"), TK_LITERAL), &tklst);
	test = create_token("1", 1, TK_LITERAL);
	test->is_delimited = 0;
	add_token_to_tklst(test, &tklst);
	add_token_to_tklst(create_token(">", 1, TK_REDIRECTION), &tklst);
	add_token_to_tklst(create_token("prout", 5, TK_LITERAL), &tklst);
	printf("--- OUTPUT ---\n");
	parse_pipeline(tklst);
	return (0);
}
