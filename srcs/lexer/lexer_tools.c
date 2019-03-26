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
