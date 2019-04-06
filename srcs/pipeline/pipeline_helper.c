#include "lexer.h"
#include "ast.h"

static char	**create_argv(t_tklst *tklst, int len)
{
	char	**res;
	int		i;

	if (!(res = malloc(sizeof(*res) * (len + 1))))
		return (NULL);
	i = 0;
	res[len] = NULL;
	while (i < len)
	{
		res[i] = ft_strdup(tklst->token->content);//strndup
		tklst = tklst->next;
		i++;
	}
	return (res);
}

char	**get_argv_from_tokens(t_tklst *tklst)
{
	int		len;
	t_tklst	*probe;

	if (!(probe = tklst))
		return (NULL);
	len = 0;
	while(probe && probe->token->type == TK_LITERAL)
	{
		len++;
		probe = probe->next;
	}
	if (len < 1)
		return (NULL);
	return (create_argv(tklst, len));
}

int	is_simple_cmd_token(t_tklst *probe)
{
	if (!probe)
		return (0);
	if (probe->token->type == TK_LITERAL
			|| probe->token->type == TK_SQ_STR
			|| probe->token->type == TK_DQ_STR
			|| probe->token->type == TK_REDIRECTION)
		return (1);
	else
		return (0);
}
