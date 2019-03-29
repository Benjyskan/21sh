#include "tosh.h"

static void	create_op_chart_elem(t_operation *op, char *str, char size, t_token_type type)
{
	ft_strcpy(op->str, str);
	op->size = size;
	op->type = type;
}

static void	fill_op_chart(t_op_chart *op_chart)
{
	create_op_chart_elem(&op_chart->op_chart[0], ">>-", 3, TK_REDIRECTION);
	create_op_chart_elem(&op_chart->op_chart[1], "$((", 3, TK_42SH);
	create_op_chart_elem(&op_chart->op_chart[2], ">>", 2, TK_REDIRECTION);
	create_op_chart_elem(&op_chart->op_chart[3], "<<", 2, TK_REDIRECTION);
	create_op_chart_elem(&op_chart->op_chart[4], "&&", 2, TK_42SH);
	create_op_chart_elem(&op_chart->op_chart[5], "||", 2, TK_42SH);
	create_op_chart_elem(&op_chart->op_chart[6], ">&", 2, TK_REDIRECTION);
	create_op_chart_elem(&op_chart->op_chart[7], "<&", 2, TK_REDIRECTION);
	create_op_chart_elem(&op_chart->op_chart[8], ">|", 2, TK_42SH);
	create_op_chart_elem(&op_chart->op_chart[9], "<>", 2, TK_42SH);
	create_op_chart_elem(&op_chart->op_chart[10], "$(", 2, TK_42SH);
	create_op_chart_elem(&op_chart->op_chart[11], "${", 2, TK_42SH);
	create_op_chart_elem(&op_chart->op_chart[12], "))", 2, TK_42SH);
	create_op_chart_elem(&op_chart->op_chart[13], "|", 1, TK_PIPE);
	create_op_chart_elem(&op_chart->op_chart[14], "<", 1, TK_REDIRECTION);
	create_op_chart_elem(&op_chart->op_chart[15], ">", 1, TK_REDIRECTION);
	create_op_chart_elem(&op_chart->op_chart[16], ";", 1, TK_SEMI);
	//
	op_chart->op_chart[17].size = 0;//end of table
}

t_op_chart	*get_op_chart(void)
{
	t_op_chart	*op_chart;

	if (!(op_chart = malloc(sizeof(op_chart))))
		return (NULL);
	fill_op_chart(op_chart);
	return (op_chart);
}

void	print_op_table(t_op_chart *op_chart)
{
	int		i;

	i = 0;
	while (op_chart->op_chart[i].size != 0)
	{
		printf("i: %d, str: {%s}, size: %d, type: %d\n",
				i,
				op_chart->op_chart[i].str,
				op_chart->op_chart[i].size,
				op_chart->op_chart[i].type);
		i++;
	}
}
