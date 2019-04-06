#include "tosh.h"

t_bool	is_quotes(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

t_bool	is_white_spaces(char c)
{
	if (c == ' ' || c == '\t' || c == '\n')
		return (1);
	return (0);
}

t_bool	is_shell_char(char c)
{
	if (is_quotes(c) || is_white_spaces(c) || c == '<' || c == '>' || c == '|')
		return (1);
	return (0);
}

t_bool	is_parenth(char c)
{
	if (c == '[' || c == ']' || c == '(' || c == ')')
		return (1);
	return (0);
}

// 
t_bool	is_metachar(char c)
{
	if (is_white_spaces(c) || is_parenth(c) || is_quotes(c) || c  == '*'
			|| c == '?' || c == '\\' || c == '$' || c == ';' || c == '&'
			|| c == '|' || c == '^' || c == '<' || c == '>')
		return (1);
	return (0);
}

/*
t_bool	is_delimiter(char c)
{
	//if (is_white_spaces(c) || c == '|' || c == '<' || c == '>' || c== ';')
	if (is_white_spaces(c))
		return (1);
	return (0);
}
*/

void	print_token(t_token *token)//debug
{
	printf("TOKEN{\n\tcontent: {%s}\n\tsize: %lu\n\ttype: %d\n\tdiscarded: %d\n\tnext: %p\n", 
			token->content,
			token->size,
			token->type,
			token->discarded,
			token->next);
}

void	print_token_list(t_token *token_head)//debug
{
	t_token	*probe;

	probe = token_head;
	while (probe)
	{
		print_token(probe);
		probe = probe->next;
	}
}
