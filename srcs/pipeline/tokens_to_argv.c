#include "lexer.h"
#include "ast.h"

/*
** Given the simple_command length, create and fills the corresponding
*/

static char		**create_argv(t_token *token, int len)
{
	char	**res;
	int		i;

	if (!(res = malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	i = 0;
	res[len] = NULL;
	while (i < len)
	{
		if (!(res[i] = ft_strdup(token->content)))
			ERROR_MEM;
		token = token->next;
		i++;
	}
	return (res);
}

t_bool	is_argv_token(t_token *probe)
{
	if (!probe)
		return (0);
	if (probe->type == TK_WORD || probe->type == TK_SQ_STR
			|| probe->type == TK_DQ_STR)
		return (1);
	return (0);
}

/*
**	Counts the length of the simple_command and asks create_simple_cmd
**	to create the corresponding 
*/

char			**get_argv_from_tokens(t_token *token)
{
	int		len;
	t_token	*probe;

	if (!(probe = token))
		return (NULL);
	len = 0;
	while(probe && is_argv_token(probe) && probe->discarded == 0)
	{
		len++;
		probe = probe->next;
	}
	if (len < 1)
		return (NULL);
	return (create_argv(token, len));
}
