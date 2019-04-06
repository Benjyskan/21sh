#include "lexer.h"
#include "ast.h"

void	redirect(int old_fd, int new_fd)
{
	if (old_fd != new_fd)
	{
		if (dup2(old_fd, new_fd) != -1)
			close(old_fd);
		else
			printf("error with dup2\n");
	}
}

int	main(void)
{
	t_tklst *tklst;;

	tklst = NULL;
	add_token_to_tklst(create_token("cat", 3, TK_LITERAL), &tklst);
	add_token_to_tklst(create_token("arborescence", ft_strlen("arborescence"), TK_LITERAL), &tklst);
	add_token_to_tklst(create_token("|", 1, TK_PIPE), &tklst);
	add_token_to_tklst(create_token("sort", 4, TK_LITERAL), &tklst);
	add_token_to_tklst(create_token("-r", 2, TK_LITERAL), &tklst);
	add_token_to_tklst(create_token("|", 1, TK_PIPE), &tklst);
	add_token_to_tklst(create_token("uniq", 4, TK_LITERAL), &tklst);
	printf("--- OUTPUT ---\n");
	parse_pipeline(tklst);
	return (0);
}
