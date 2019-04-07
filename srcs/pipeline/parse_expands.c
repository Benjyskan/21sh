#include "lexer.h"
#include "ast.h"

/*
** parses_quotes, changes from a t_token array pointer to a char* array,
** and calls execve on the array
*/

int		parse_quotes(t_token **argv)
{
	int i;

	(void)argv;
	i = 0;
	while (argv[i])
	{
		dprintf(2, "QUOTES: argv[%d]:\t", i);
		while (argv[i] && argv[i]->type != TK_EAT && argv[i]->type != TK_PIPE)
		{
			dprintf(2, "%s\t", argv[i]->content);
			argv[i] = argv[i]->next;
		}
		dprintf(2, "\n");
		i++;
	}
	return (1);
}

/*
** parses_expands and hands the argv to parse_quotes
*/

static char	*expand_string(char *str)
{
	char *res;

	if (ft_strchr(str, '$'))
		printf("found!");
	res = ft_strdup("YOOOO"); // need to change type size !
	free(str);
	return (res);
}

int		parse_expands(t_token **argv)
{
	int		i;

	i = 0;
	while (argv[i])
	{
		if (argv[i]->type == TK_DQ_STR || argv[i]->type == TK_WORD) //missing a while (argv[i]->next)
		{
			argv[i]->content = expand_string(argv[i]->content);
			argv[i]->size = ft_strlen(argv[i]->content);
		}
		i++;
	}
	return (parse_quotes(argv));
}
