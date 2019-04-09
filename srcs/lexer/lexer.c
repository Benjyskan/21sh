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

t_bool	add_token_to_list(t_token *current_token, t_token *prev_token
		, t_token **token_head)
{
	t_token	*probe;

	if ((!prev_token && current_token->type > TK_HEREDOC)//						check if it start with CTRL_OP
			|| (prev_token && (current_token->type > TK_DQ_STR//				check if 2 REDIR or CTRL_OP a la suite
				&& prev_token->type > TK_DQ_STR)))//							""
	{
		printf("111\n");
		syntax_error_near(current_token);
		return (0);
	}
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

t_token	*lexer(char *cmdline, char **env)
{
	t_token		*token_head;
	t_token		*current_token;
	t_operation	*op_chart;
	t_token		*prev_token;

	op_chart = get_op_chart();
	token_head = NULL;
	prev_token = NULL;
	while (cmdline && *cmdline)
	{
		if (!(current_token = get_token(&cmdline, op_chart)))
		{
			ERROR_MEM;//														check with a correct reader//check what happen on 'unquoted'
			return (NULL);
		}
		if (!(add_token_to_list(current_token, prev_token, &token_head)))//recover unexpexted delete*
			return (NULL);//free token list
		if (current_token->type != TK_EAT)
			prev_token = current_token;
	}
	if (is_and_or_token(current_token)//check if cmdline end with '&&'
			|| (is_and_or_token(prev_token) && !current_token->type))//			check if cmdline end with '&&' with only TK_EAT after
	{
		ft_putendl("tmp, tklst end with '&&' or '||': READ_MODE");
		return (NULL);//TMP
	}
	//test
	//bash tokenise 'newline', it make easier to check "cat << <ENTER>"
	else if (prev_token && (prev_token->type > TK_DQ_STR && (current_token->type == TK_EAT || current_token->type > TK_DQ_STR)))
	{
		ft_putendl("222");
		syntax_error_near(current_token);
		return (NULL);
	}
	//endtest
	printf("prev: {%s}, curr: {%s}\n", prev_token->content, current_token->content);
	return (token_head);
}
