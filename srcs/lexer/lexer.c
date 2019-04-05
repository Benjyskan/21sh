#include "tosh.h"
#include "lexer.h"
#include "ast.h"

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

t_tklst	*lexer(char *cmdline, char **env)
{
	t_tklst		*tklst_head;
	t_token		*current_token;
	t_op_chart	*op_chart;

	op_chart = get_op_chart();//protect me && free me //should it be earlier ??
	print_op_table(op_chart);//debug tejme
	tklst_head = NULL;
	while (cmdline && *cmdline)
	{
		if (is_white_spaces(*cmdline))
		{
			cmdline++;
			continue ;
			//or create a TK_EAT while is_white_spaces(*cmdline)
		}
		if (!(current_token = get_token(&cmdline, op_chart)))
			return (NULL);
		printf("CMDLINE: {%s}\n", cmdline);
		add_token_to_tklst(current_token, &tklst_head);
	}
	//ft_memdel((void*)op_chart);
	//should i add a NULL token ?
	return (tklst_head);
}
