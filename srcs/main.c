#include "tosh.h"

char	*ft_realloc(void *data, size_t current_data_size,
		size_t *current_malloc_size, size_t append_size)
{
	char	*res;

	if (current_data_size + append_size < *current_malloc_size)
		return (data);
	res = ft_strnew(*current_malloc_size * 2);
	*current_malloc_size *= 2;
	res = (char*)ft_memcpy((void*)res, (void*)data, current_data_size);
	ft_memdel((void*)&data);
	return (res);
}

void	read_stdin(char **cmd, char **env)//cpy de skod
{
	int		ret;
	char	buf;
	int		i;
	size_t	mall_size;

	(void)env;//tejme
	print_prompt();
	mall_size = BUF_SIZE;
	i = 0;
	buf = 0;
	while ((ret = read(0, &buf, 1) > 0) && buf && buf != '\n')
	{
		*cmd = ft_realloc((void*)*cmd, ft_strlen(*cmd), &mall_size, ret);
		ft_strncat((*cmd + i++), &buf, 1);
	}
	if (buf == '\n')
		return ;
	else if (ret == 0)
		exit (1);//error_exit(*cmd, env);
	else if (ret < 0 || (!buf && ret))
		ERROR_READ;
}

static int	is_str_empty(char *str)
{
	int		i;

	i = -1;
	while (str[++i])
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != ';')
			return (0);
	}
	return (1);
}

int		main(int argc, char **argv, char **env)
{
	char	**env_cpy;
	char	*input;

	(void)argc;
	(void)argv;
	if (!(env_cpy = init_env(env)))
		return (1);
	while (42)
	{
		if (!(input = ft_strnew(BUF_SIZE)))
			ERROR_MEM;
		read_stdin(&input, env_cpy);
		if (!*input || is_str_empty(input))
		{
			ft_memdel((void*)&input);
			continue ;
		}
		if (!(handle_input(input, env_cpy)))
			ft_memdel((void*)&input);
	}
	ft_free_nultab(env_cpy);
	return (0);
}
