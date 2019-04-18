#include "lexer.h"
#include "ast.h"

static t_bool	is_env_var_name_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

static char		*get_var_name(char *str)
{
	size_t		i;
	char	*var_name;

	str++;
	i = 0;
	while (str[i] && is_env_var_name_char(str[i]))//should i check $$ ?
		i++;
	if (i == 0)
		return (NULL);
	if (!(var_name = ft_strndup(str, i)))
		ERROR_MEM;
	return (var_name);
}

static char		*substitute_env_var(char *old_str, size_t *i
		, char *var_value, char *var_name)
{
	char	*new_str;

	if (!(new_str = ft_strnew(ft_strlen(old_str)
					- (ft_strlen(var_name) + 1) + ft_strlen(var_value))))
		ERROR_MEM;
	ft_strncpy(new_str, old_str, *i);
	ft_strcpy(new_str + *i, var_value);
	*i += ft_strlen(var_value);
	ft_strcpy(new_str + *i
			, old_str + *i - ft_strlen(var_value) + (ft_strlen(var_name) + 1));
	--(*i);
	ft_memdel((void*)&old_str);
	ft_memdel((void*)&var_name);
	old_str = new_str;
	return (new_str);
}

static t_bool	expand_dollars(t_token *token_head, char **env)
{
	size_t	i;
	char 	*var_name;
	char	*var_value;

	i = 0;
	while (token_head->content[i])
	{
		if (token_head->content[i] == '$')
		{
			if (!(var_name = get_var_name(token_head->content + i)))
			{
				ft_putendl("get_var_name returned NULL, ignoring this '$'");
				i++;
				continue ;
			}
			if (!(var_value = get_envline_value(var_name, env)))
				var_value = &var_name[ft_strlen(var_name)];//on peut difficilement faire pire, la degueulasserie a son paroxysme !
			token_head->content = substitute_env_var(token_head->content, &i
					, var_value, var_name);
		}
		i++;
	}
	return (0);
}

t_bool			parse_dollars(t_token *token_head, char** env)
{
	t_bool	res;

	res = 0;
	while (token_head && token_head->type < TK_PIPE)
	{
		if (token_head->type == TK_WORD || token_head->type == TK_DQ_STR)
		{
			res = 1;
			expand_dollars(token_head, env);
		}
		token_head = token_head->next;
	}
	return (res);
}
