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
		ft_memdel((void*)&new_token);//TODO check me
		ft_putendl_fd("malloc failed in create_token", STDERR_FILENO);
		return (NULL);
	}
	//print_token(new_token);//debug
	return (new_token);
}

void	add_token_to_list(t_token *token, t_token **token_head)
{
	t_token	*probe;

	if (!(*token_head))
	{
		*token_head = token;
		return ;
	}
	probe = *token_head;
	while (probe->next)
		probe = probe->next;
	probe->next = token;
	return ;
}

t_token	*lexer(char *cmdline, char **env)
{
	t_token		*token_head;
	t_token		*current_token;
	t_operation	*op_chart;
	t_token		*prev_token;

	op_chart = get_op_chart();
	//print_op_table(op_chart);//debug
	token_head = NULL;
	prev_token = NULL;
	while (cmdline && *cmdline)
	{
		if (!(current_token = get_token(&cmdline, op_chart)))
			return (NULL);
		//printf("CMDLINE: {%s}\n", cmdline);
		if (prev_token && (current_token->type > TK_DQ_STR
					&& prev_token->type > TK_DQ_STR))
		{
			ft_putstr("NEW ");
			syntax_error_near(current_token);
			return (NULL);
		}
		if (prev_token && prev_token->type == TK_HEREDOC
				&& current_token->type != TK_EAT)//check HEREDOC
		{
			printf("HEREDOC, enter READ_MODE, with EOF: {%s}\n", current_token->content);
		}
		add_token_to_list(current_token, &token_head);
		if (current_token->type != TK_EAT)
			prev_token = current_token;
	}
	if (is_and_or_token(current_token))
	{
		ft_putendl("tmp, tklst end with '&&' or '||': READ_MODE");
		return (NULL);//TMP
	}
	//ft_memdel((void*)op_chart);
	return (token_head);
}
