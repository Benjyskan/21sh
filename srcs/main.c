#include "lexer.h"
#include "ast.h"

int	main(void)
{
	t_tklst *tklst;;

	tklst = NULL;
	add_token_to_tklst(create_token("cat", 3, TK_LITERAL), &tklst);
	add_token_to_tklst(create_token("test", ft_strlen("test"), TK_LITERAL), &tklst);
	add_token_to_tklst(create_token("|", 1, TK_PIPE), &tklst);
	add_token_to_tklst(create_token("sort", 4, TK_LITERAL), &tklst);
	add_token_to_tklst(create_token("|", 1, TK_PIPE), &tklst);
	add_token_to_tklst(create_token("uniq", 4, TK_LITERAL), &tklst);
	printf("--- OUTPUT ---\n");
	parse_pipeline(tklst);
	return (0);
}
