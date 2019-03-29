#include "tosh.h"

/*
   char	check_state(char c, t_parser_state *state)
   {
   if (*cmdline == '"' && state == IN_CMD)
 *state = IN_DQUOT;
 else if (*cmdline == '"' && state == D_QUOT)
 *state = IN_CMD;
 else if (*cmdline == ''' && state == IN_CMD)
 *state = IN_QUOT;
 else if (*cmdline == ''' && state == IN_QUOT)
 *state = IN_CMD;
 }
 */

/*
static unsigned char	init_token(t_token *token)//useless return value
{
	if (!(token = malloc(sizeof(t_token))))
		return (0);
	token->content = NULL;
	token->size = 0;
	token->type = 0;
	token->is_delimited = 0;
	return (1);
}

t_token			*get_normal_token(char *cmdline)
{
	t_token			*token;
	unsigned int	i;

	if (!(init_token(token)))
		return (NULL);
	i = 0;
	while (!is_shell_char(cmdline[i]))
		i++;
	token->is_delimited = (is_quotes(cmdline[i]) ? 0 : 1);
	if (!(token->content = ft_strndup(cmdline, i)))
		return (NULL);
	token->size = i;
	token->type = TK_LITERAL;
	return (token);
}

t_token	get_token(char **cmdline)
{
	//if (**cmdline == '"' || **cmdline == '\'')
	if (is_quotes(**cmdline))
		return (get_quote_token(*cmdline));
	else if (**cmdline == '>' || **cmdline == '<' || **cmdline == '|')
		return (get_redir_token(*cmdline));
	else
		return (get_normal_token(*cmdline));
}

int		tokenise(char *cmdline, t_tklst **tklst_head, char **env)
{
	t_parser_state	state;

	state = IN_CMD;
	if (!tklst_head)
		init_tklst(tklst_head);
	while (cmdline && *cmdline++)
	{
		//check_state(*cmdline, &state);
		if (!(get_token(&cmdline)))
			return (0);
	}
	return (1);
}
*/

t_token	*create_token(char *cmdline, size_t size, t_token_type type)
{
	t_token	*new_token;

	if (!(new_token = malloc(sizeof(t_token))))
		return (NULL);
	new_token->size = size;
	new_token->type = type;
	if (!(new_token->content = ft_strndup(cmdline, size)))
		return (NULL);
	if (is_delimiter(cmdline[size]) || cmdline[size] == 0)
		new_token->is_delimited = 1;
	else
		new_token->is_delimited = 0;
	print_token(new_token);
	return (new_token);
}

/*
t_token	*get_token(t_tklst **tklst_head, char **cmdline)
{
	t_token	*token;
	char	*prev_pos;
	size_t	i;	

	printf("GET_TOK START: cmdline: {%s}\n", *cmdline);
	prev_pos = *cmdline;
	i = 0;
	if (is_metachar(**cmdline))
	{
		printf("Is metachar !!\n");
		//return (NULL);//tmp
	}
	else
	{
		while ((*cmdline)[i] && !is_metachar((*cmdline)[i]))
			i++;
		printf("current cmdline: {%s}\n", *cmdline);
		//return (create_token(*cmdline, i, TK_LITERAL));
		if (!(token = create_token(*cmdline, i, TK_LITERAL)))
			return (NULL);
		*cmdline = (*cmdline) + i - 0;
		printf("GET_TOKEN_END: {%s}\n", *cmdline);
	}
	return (token);//useless
}
*/

/*
** lexer
** should tokenise the cmdline and return a pointer to the head of the list;
*/

/*
//check cmdline entry ?
t_tklst	*lexer(char *cmdline, char **env)
{
	t_tklst			*tklst_head;
	t_lexer_state	state;
	t_token			*current_token;

	printf("LEXER START, cmdline: {%s}\n", cmdline);
	tklst_head = NULL;
	state = LEX_NORMAL;
	while (cmdline && *cmdline)
	{
		//setup_state(&state...
		if (*cmdline == '\\' && state != LEX_IN_SQUOT)
		{
			cmdline++; printf("debug: '/' leap\n");
			continue ;
		}
		if (!(current_token = get_token(&tklst_head, &cmdline)))
			return (NULL);
		//add token to tklst
		if (is_white_spaces(*cmdline))
			cmdline++;
		//cmdline++;
	}
	printf("----------------");
	print_token_list(tklst_head);
	return (tklst_head);
}
*/

t_tklst	*create_tklst_node(t_token *token)
{
	t_tklst	*tklst_node;

	if (!(tklst_node = malloc(sizeof(tklst_node))))
		return (NULL);
	tklst_node->token = token;
	tklst_node->next = NULL;
	return (tklst_node);
}

t_bool	add_token_to_tklst(t_token *token, t_tklst **tklst_head)
{
	t_tklst	*probe;

	if (*tklst_head == NULL)
	{
		if (!(*tklst_head = create_tklst_node(token)))
			return (0);
		printf("in add_to_tklst: {%s}\n", (*tklst_head)->token->content);
		return (1);
	}
	probe = *tklst_head;
	while (probe->next)
		probe = probe->next;
	if (!(probe->next = create_tklst_node(token)))
		return (0);
	return (1);
}

t_token	*get_dquot_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 1;
	while ((*cmdline)[i] && (*cmdline)[i] != '"')
	{
		if ((*cmdline)[i] == '\\')
			i++;
		i++;
	}
	if ((*cmdline)[i] == 0)
	{
		ft_putendl_fd("Unmatched \".", 2);
		return (NULL);
	}
	if (!(token = create_token(*cmdline, ++i, TK_DQ_STR)))
	{
		ft_putendl_fd("malloc failed on create_token", 2);
		return (NULL);
	}
	*cmdline = *cmdline + i;
	return (token);
}

t_token	*get_squot_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 1;
	while ((*cmdline)[i] && (*cmdline)[i] != '\'')
		i++;
	if ((*cmdline)[i] == 0)
	{
		ft_putendl_fd("Unmatched '.", 2);
		return (NULL);
	}
	if (!(token = create_token(*cmdline, ++i, TK_SQ_STR)))
	{
		ft_putendl_fd("malloc failed on create_token", 2);
		return (NULL);
	}
	*cmdline = *cmdline + i;
	return (token);
}

t_token	*get_regular_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	printf("get_regular_token received: {%s}\n", *cmdline);
	i = 0;
	while ((*cmdline)[i] && !is_metachar((*cmdline)[i]))
		i++;
	if (!(token = create_token(*cmdline, i, TK_LITERAL)))
		return (NULL);
	*cmdline = *cmdline + i;
	return (token);
}

t_token	*get_redir_token(char **cmdline)
{
	t_token	*token;
	size_t	i;

	i = 0;
	//tmp NEED REDIRECTION SYNTAX !!
	while ((*cmdline)[i] && !is_metachar((*cmdline)[i]))
		i++;
	if (!(token = create_token(*cmdline, i, TK_REDIRECTION)))
		return (NULL);
	*cmdline = *cmdline + i;
	return (token);
	//end tmp
}

t_token	*get_monochar(char **cmdline)
{
	t_token	*token;

	if (!(token = create_token(*cmdline, 1, TK_LITERAL)))
		return (NULL);
	*cmdline = *cmdline + 1;
	return (token);
}

t_token	*check_if_redir_or_literal(char **cmdline)
{
	size_t	i;

	i = 0;
	while ((*cmdline)[i] && ft_isdigit((*cmdline)[i]))
		i++;
	if (is_white_spaces((*cmdline)[i]) || ft_isalpha((*cmdline)[i])
			|| (*cmdline)[i] == '\\')
		return (get_regular_token(cmdline));
	else
		return (get_redir_token(cmdline));//ICI
}

t_token	*get_token(char **cmdline)
{
	//should i strncmp(*cmdline with a table of pattern ??
	system("read -p \"Press enter to continue\"");
	if (**cmdline == '"')
		return (get_dquot_token(cmdline));
	else if (**cmdline == '\'')
		return (get_squot_token(cmdline));
	else if (ft_isdigit(**cmdline) || is_redir(**cmdline))//change this
		return (check_if_redir_or_literal(cmdline));//check if it is redir or literal
	else if (**cmdline == '\\')
	{
		(*cmdline)++;
		return (get_monochar(cmdline));
	}
	else//bof, need other conditions
		return (get_regular_token(cmdline));
}

t_tklst	*lexer(char *cmdline, char **env)
{
	t_tklst		*tklst_head;
	t_token		*current_token;
	t_op_chart	*op_chart;

	op_chart = get_op_chart();//protect me && free me //should it be earlier ??
	print_op_table(op_chart);//debug
	tklst_head = NULL;
	while (cmdline && *cmdline)
	{
		if (is_white_spaces(*cmdline))
		{
			cmdline++;
			continue ;
		}
		//get_right_token
		if (!(current_token = get_token(&cmdline)))//protect
			return (NULL);
		printf("CMDLINE: {%s}\n", cmdline);
		add_token_to_tklst(current_token, &tklst_head);
	}
	//ft_memdel((void*)op_chart);
	return (tklst_head);
}
