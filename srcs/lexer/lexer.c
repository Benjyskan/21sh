#include "tosh.h"
#include "lexer.h"
//#include "ast.h"

t_token	*create_token(char *cmdline, size_t size, t_token_type type)
{
	t_token	*new_token;

	if (!(new_token = (t_token*)malloc(sizeof(t_token))))
	{
		ft_putendl_fd("malloc failed in create_token", STDERR_FILENO);
		return (NULL);
	}
	new_token->size = size;
	new_token->type = type;
	new_token->next = NULL;
	if (!(new_token->content = ft_strndup(cmdline, size)))
	{
		ft_memdel((void*)&new_token);
		ft_putendl_fd("malloc failed in create_token", STDERR_FILENO);
		return (NULL);
	}
	//print_token(new_token);//debug
	return (new_token);
}

static t_bool	add_token_to_list(t_token *current_token, t_token *prev_token
				, t_token **token_head)
{
	t_token	*probe;

	if (token_list_start_with_ctrl_op(prev_token, current_token)
			|| is_two_ctrlop_or_redir_following(prev_token, current_token))
		return (0);
	if (prev_token && prev_token->type == TK_HEREDOC
			&& current_token->type != TK_EAT)
	{
		printf("HEREDOC, enter READ_MODE, with EOF: {%s}\n", current_token->content);
		//bash:syntax error near unexpected token `newline'; should i tokenise '\n' ??
	}
	if (!(*token_head))
	{
		*token_head = current_token;
		return (1);
	}
	probe = *token_head;
	while (probe->next)
		probe = probe->next;
	probe->next = current_token;
	return (1);
}

/*
** init_lexer
** set the variables the lexer needs
*/

static void	init_lexer(t_operation **op_chart, t_token **token_head
			, t_token **prev_token)
{
	*op_chart = get_op_chart();
	*token_head = NULL;
	*prev_token = NULL;
}

/*
** lexer
** run through the cmdline and tokenize it
*/

t_token	*lexer(char *cmdline, char **env)
{
	t_token		*token_head;
	t_token		*current_token;
	t_operation	*op_chart;
	t_token		*prev_token;

	init_lexer(&op_chart, &token_head, &prev_token);
	while (cmdline && *cmdline)
	{
		if (!(current_token = get_token(&cmdline, op_chart)))
		{
			ERROR_MEM;//check with a correct reader//check what happen on 'unquoted'
			return (NULL);
		}
		if (!(add_token_to_list(current_token, prev_token, &token_head)))
			return (NULL);//free token list
		if (current_token->type != TK_EAT)
			prev_token = current_token;
	}
	printf("prev: {%s}, curr: {%s}\n", prev_token->content, current_token->content);//debug
	if (is_logic_or_pipe(current_token)
			|| (is_logic_or_pipe(prev_token) && !current_token->type))
	{
		ft_putendl("tmp, tklst end with '&&','||' or '|': READ_MODE");
		return (NULL);//TMP
	}
	//bash tokenise 'newline', it make easier to check "cat << <ENTER>"
	else if (prev_token && is_redir_token(prev_token)
			&& (!current_token->type || is_redir_token(current_token)))
	{
		ft_putstr("222");
		syntax_error_near(current_token);
		return (NULL);
	}
	return (token_head);
}
