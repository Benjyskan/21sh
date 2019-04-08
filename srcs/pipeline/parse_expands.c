#include "lexer.h"
#include "ast.h"

/*
** parses_quotes, changes from a t_token array pointer to a char* array,
** and calls execve on the array
*/

int		parse_quotes(t_token **argv)
{
	int		i;
	t_token	*probe;

	(void)argv;
	i = 0;
	while (argv[i])
	{
		probe = argv[i];
		while (probe && probe->type != TK_EAT && probe->type != TK_PIPE)
			probe = probe->next;
		i++;
	}
	print_token_tab(argv);
	return (1);
}

static char	*expand_string(char *str)
{
	char *res;

	if (ft_strchr(str, '$'))
	{
		printf("found a $\n");
		res = ft_strdup("YOOOO"); // need to change type size !
		free(str);
	}
	else
		res = str;
	return (res);
}

/*
** parses_expands and hands the argv to parse_quotes
*/

int		parse_expands(t_token **argv)
{
	int		i;
	t_token *probe;

	i = 0;
	while (argv[i])
	{
		probe = argv[i];
		while (probe && (probe->type == TK_DQ_STR || probe->type == TK_WORD))
		{
			probe->content = expand_string(probe->content);
			probe->size = ft_strlen(probe->content);
			probe = probe->next;
		}
		i++;
	}
	return (parse_quotes(argv));
}
