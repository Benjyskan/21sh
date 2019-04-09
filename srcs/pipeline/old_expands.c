#include "lexer.h"
#include "ast.h"

static char	*concatenate_tokens(t_token *token)
{
	int		len;
	t_token	*probe;
	char	*res;

	if (!(probe = token))
		return (NULL);
	len = 0;
	while (probe && probe->type == TK_EAT)
		probe = probe->next;
	while (is_argv_token(probe))
	{
		len += ft_strlen(probe->content);
		probe = probe->next;
	}
	if (!len)
		return  (NULL);
	else if (!(res = ft_strnew(len)))
		ERROR_MEM;
	probe = token;
	while (probe && probe->type == TK_EAT)
		probe = probe->next;
	while (is_argv_token(probe))
	{
		res = ft_strcat(res, probe->content);
		probe = probe->next;
	}
	dprintf(2, "TOKEN: [%s], RES: {%s}\n", token->content, res);
	return (res);
}

/*
** parses_quotes, changes from a t_token array pointer to a char* array,
** and calls execve on the array
*/

int		execute_command(t_token **token_argv)
{
	char	**argv;
	int		i;

	i = 0;
	argv = (char**)token_argv;
	dprintf(2, "-- EXEC -- \n");
	dprintf(2, "TOKEN_ARGV[0], %s\n", (token_argv[0])->content);
	while (token_argv[i])
	{
		dprintf(2, "CONCATENATING\n");
		argv[i] = concatenate_tokens(token_argv[i]);
		i++;
	}
	dprintf(2, "executing: %s\n", argv[0]);
	i = 0;
	while (argv[i])
	{
		dprintf(2, "argv[%d], %s\n", i, argv[i]);
		i++;
	}
	dprintf(2, "argv[%d], %s\n", i , argv[i]);
	execvp(argv[0], (char * const*)argv);
	dprintf(2, "EXEC RETURNED -1\n");
	return (0);
}

t_bool	is_quote_token(t_token *probe)
{
	if (!probe)
		return (0);
	if (probe->type == TK_SQ_STR || probe->type == TK_DQ_STR)
		return (1);
	else
		return (0);
}

int		parse_quote(t_token **token_argv)
{
	int		i;
	t_token	*probe;
	char	*old_content;

	i = 0;
	while (token_argv[i])
	{
		probe = token_argv[i];
		while (probe && probe->type != TK_EAT && probe->type != TK_PIPE)
		{
			if (is_quote_token(probe))
			{
				old_content = probe->content;
				if (!(probe->content = ft_strndup((const char*)&(*(probe->content + 1)), ft_strlen(probe->content) - 2)))
					ERROR_MEM;
				free(old_content);
			}
			probe = probe->next;
		}
		i++;
	}
	execute_command(token_argv);
	return (1);
}

static char	*expand_string(char *str)
{
	char *res;

	if (ft_strchr(str, '$'))
	{
		dprintf(2, "found a $\n");
		if (!(res = ft_strdup("YOOOO"))) // need to change type size ! check null
			ERROR_MEM;
		free(str);
	}
	else
		res = str;
	return (res);
}

/*
** parses_expands and hands the token_argv to parse_quotes
*/

int		parse_expands(t_token **token_argv)
{
	int		i;
	t_token *probe;

	i = 0;
	while (token_argv[i])
	{
		probe = token_argv[i];
		while (probe && (probe->type == TK_DQ_STR || probe->type == TK_WORD))
		{
			probe->content = expand_string(probe->content);
			probe->size = ft_strlen(probe->content);
			probe = probe->next;
		}
		i++;
	}
	return (parse_quote(token_argv));
}
