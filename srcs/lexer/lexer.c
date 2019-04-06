#include "tosh.h"
#include "lexer.h"
#include "ast.h"

//t_tklst	*lexer(char *cmdline, char **env)
t_token	*lexer(char *cmdline, char **env)
{
	t_token		*token_head;
	t_token		*current_token;
	t_op_chart	*op_chart;

	op_chart = get_op_chart();//protect me && free me //should it be earlier ??
	print_op_table(op_chart);//debug tejme
	token_head = NULL;
	while (cmdline && *cmdline)
	{
		if (!(current_token = get_token(&cmdline, op_chart)))
			return (NULL);
		printf("CMDLINE: {%s}\n", cmdline);
		add_token_to_list(current_token, &token_head);
	}
	//ft_memdel((void*)op_chart);
	//should i add a NULL token ?
	return (token_head);
}
