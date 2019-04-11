#include "lexer.h"
#include "ast.h"

static t_bool	tild_expand(t_token *token)
{
	char	*old_content;

	if (*token->content == '~')
	{
		old_content = token->content;
		if (!(token->content = ft_strndup("TILD", 4))) // look for environement functions to get value from key "HOME" and protect the function
			ERROR_MEM;
		free(old_content);
		return (1);
	}
	return (0);
}

/*
t_bool	parse_tildes(t_token *token_head)
{
	t_bool	res;

	res = 0;
	while (token_head && token_head->type < TK_PIPE)
	{
		if (token_head->type == TK_WORD || token_head->type == TK_DQ_STR)
		{
			res = 1;
			tild_expand(token_head, env);
		}
		token_head = token_head->next;
	}
	return (res);
}
*/

static t_bool	is_valid_tilde(t_token *curr_token, t_token *prev_token)
{
	if (!prev_token && (!ft_strncmp("~", curr_token->content, 2)
				|| !ft_strncmp("~/", curr_token->content, 2)))
		return (1);
	else if (prev_token && prev_token->type == TK_EAT
			&& (!ft_strncmp("~", curr_token->content, 2)
				|| !ft_strncmp("~/", curr_token->content, 2)))
		return (1);
	return (0);
}

static t_bool	replace_tilde(char **str, char **env)
{
	char	*new_str;
	char	*home_str;

	home_str = get_envline_value("HOME", env);//protect if not found
	if (!(new_str = ft_strnew(ft_strlen(home_str) + ft_strlen(*str) - 1)))
		ERROR_MEM;
	ft_strcpy(new_str, home_str);
	ft_strcat(new_str, *(&str[1]));
	ft_memdel((void*)*(&str));
	*str = new_str;
	return (1);
}

t_bool	parse_tildes(t_token *token_head, char **env)
{
	t_token *prev_token;
	t_token *curr_token;
	
	curr_token = token_head;
	prev_token = NULL;
	ft_putendl("##########in Parse_tildes");
	while (curr_token)
	{
		if (curr_token->type == TK_WORD && is_valid_tilde(curr_token, prev_token))//~ doesn't expand in ""
		{
			printf("OUAI, {%s}\n", curr_token->content);
			replace_tilde(&curr_token->content, env);
			printf("NOW: {%s}\n", curr_token->content);
		}
		prev_token = curr_token;
		curr_token = curr_token->next;
	}
	ft_putendl("################");
	return (1);//tmp
}
