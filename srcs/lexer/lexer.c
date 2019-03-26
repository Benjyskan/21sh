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
	if (**cmdline == '"' || **cmdline == '\'')
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

/*
** for each cmdline in the list
*/

//LEXER WON'T RECEIVE NULL CMD
int		lexer(t_cmdlst *cmdlst, char **env)
{
	t_tklst		*tklst_head;

	tklst_head = NULL;
	//tokenise(probe->cmdline, &tklst_head, env);
	return (1);
}
