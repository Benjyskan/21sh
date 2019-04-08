#include "lexer.h"
#include "ast.h"

/*
** Given the simple_command length, create and fills the corresponding
** argv.
*/

static t_token		**create_argv(t_token *token, int argv_len)
{
	t_token	**res;
	int		i;

	if (!(res = (t_token**)malloc(sizeof(*res) * (argv_len + 1))))
		return (NULL);
	i = 0;
	res[argv_len] = NULL;
	printf("argv_len: %d\n", argv_len);
	while (i < argv_len)
	{
		while (token && token->type == TK_EAT)
			token = token->next;
		res[i] = token;
		while (is_argv_token(token))
			token = token->next;
		i++;
	}
	return (res);
}

t_bool	is_argv_token(t_token *probe)
{
	if (!probe)
		return (0);
	if (probe->type == TK_WORD || is_quote_token(probe))
		return (1);
	return (0);
}

/*
**	Counts the length of the simple_command and asks create_simple_cmd
**	to create the corresponding 
*/

t_token		**get_argv_from_tokens(t_token *token)
{
	int		argv_len;
	t_token	*probe;

	if (!(probe = token))
		return (NULL);
	argv_len = 0;
	while (probe)
	{
		while (probe && is_argv_token(probe))
			probe = probe->next;
		argv_len++;
		while (probe && probe->type == TK_EAT)
			probe = probe->next;
	}
	if (argv_len < 1)
		return (NULL);
	dprintf(2, "Length of token_array: %d, %s\n", argv_len, token->content);
	return (create_argv(token, argv_len));
}
