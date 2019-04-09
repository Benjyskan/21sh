#include "lexer.h"
#include "ast.h"

/*
** Functions that expans words in this order:
**		- Tilde
**		- $
**		- Quote removal
**	Then calls parse_redir to look for redirections
*/

t_bool		parse_redirections(t_token *token_head)
{
	return (1);
}

t_bool		parse_expands(t_token *token_head, int in, int out)
{
	redirect(in, STDIN_FILENO);
	redirect(out, STDOUT_FILENO);
	parse_tildes(token_head);
	parse_dollars(token_head);
	parse_quotes(token_head);
	return (parse_redirections(token_head));
}
