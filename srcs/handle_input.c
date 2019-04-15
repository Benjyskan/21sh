#include "tosh.h"
#include "lexer.h"
#include "ast.h"

void	read_more(char **input)
{
	size_t	i;
	int		read_ret;
	char	c;
	size_t	j;

	i = 0;
	j = 0;
	while ((*input)[i])
		i++;
	ft_putstr("> ");
	while ((read_ret = read(STDIN_FILENO, &c, 1) > 0))
	{
		if (read_ret == -1)
			printf("READ_ERROR -1\n");
		else if (read_ret == 0)
			printf("read return 0\n");
		(*input)[i++] = c;
		if (c == '\n')
		{
			if (i > 0)//useless line ?
				(*input)[i - 1] = 0;
			else
				printf("BUG\n");
			printf("--break\n");
			break ;
		}
	}
}

/*
** handle_input
** should pass the inputed cmdline through the lexer to get a token list;
** then create the ast with the token list
** then execute the ast ?
*/

t_bool	handle_input(char *input, char **env)
{
	t_ast			*ast_root;
	t_token			*token_head;
	int				lexer_ret;

	while ((lexer_ret = lexer(input, &token_head, env)) == LEX_CONT_READ)
	{
		read_more(&input);
		printf("NEW_INPUT: {%s}\n", input);
	}
	if (lexer_ret == LEX_FAIL)
	{
		printf("\x1B[31m""### Lexer FAILED""\x1B[0m""\n");
		return (0);
	}
	else
		printf("\x1B[32m""### lexer SUCCESS""\x1B[0m""\n");
	printf("POST LEXER: input: {%s}\n", input);
	ft_memdel((void*)&input);
	//print_token_list(token_head);
	if (!(ast_root = create_ast(token_head)))
	{
		printf("\x1B[31m""### Parser FAILED""\x1B[0m""\n");
		return (0);
	}
	printf("\x1B[32m""### Parser SUCCESS""\x1B[0m""\n");
	//print_ast(ast_root);
	exec_ast(ast_root, env);
	ft_putendl("THE END");
	free_ast(ast_root);
	//print_ast(ast_root);
	return (1);
}
