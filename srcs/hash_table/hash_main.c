#include "hashmap.h"

static void	print_bits(unsigned char c)//debug
{
	if (!c)
		return ;
	else
		print_bits(c >> 1);
	if (c & 1)
		printf("1");
	else
		printf("0");
}

typedef struct	s_hash_args
{
	unsigned char	opt;
	char			*path;
	//char			**name;//useless
	unsigned int	name_index;
	unsigned char	state;
}				t_hash_args;

typedef enum	e_hash_opt
{
	//O_P = 0b1,
	O_L = 0b1,
	O_D = 0b10,
	//O_T = 0b100,
	O_R = 0b100
}				t_hash_opt;

typedef enum	e_hash_state
{
	GET_OPT,
	GET_PATH,
	GET_NAME,
	GET_DONE
}				t_hash_state;

static t_hash_args	*init_hash_args(void)
{
	t_hash_args	*hash_args;

	hash_args = (t_hash_args*)malloc(sizeof(*hash_args));
	hash_args->opt = 0;
	hash_args->path = NULL;
	//hash_args->name = NULL;//useless
	hash_args->name_index = 0;
	hash_args->state = GET_OPT;
	return (hash_args);
}

static t_bool			get_hash_opt(char *arg, t_hash_args *hash_args)
{
	int	i;

	if (!arg[1])
		hash_args->state = GET_NAME;
	i = 0;
	while (arg[++i])
	{
		if (arg[i] == 'p')
		{
			if (arg[i + 1])
			{
				hash_args->path = &arg[i + 1];
				hash_args->state = GET_NAME;
				return (1);
			}
			else
				hash_args->state = GET_PATH;
		}
		else if (arg[i] == 'l')
			hash_args->opt = hash_args->opt | O_L;
		else if (arg[i] == 'd')
			hash_args->opt = hash_args->opt | O_D;
		//else if (arg[i] == 't')
		//	hash_args->opt = hash_args->opt | O_T;
		else if (arg[i] == 'r')
			hash_args->opt = hash_args->opt | O_R;
		else
		{
			ft_dprintf(2, "-%c: invalid option\n", arg[i]);
			//print_usage();
			printf("hash [-lr] [-p pathname] [-d] [name ...]\n");//no 't'
			return (0);
		}
	}
	return (1);
}

static t_hash_args	*get_hash_args(int argc, char **argv)
{
	t_hash_args	*hash_args;
	int			i;

	hash_args = init_hash_args();
	i = 0;
	while (++i < argc)
	{
		if (hash_args->state == GET_NAME)
		{
			printf("getting name: {%s}\n", argv[i]);
			hash_args->name_index = i;
			hash_args->state = GET_DONE;
			printf("with name_index: {%d}\n", hash_args->name_index);
		}
		else if (hash_args->state == GET_PATH)
		{
			hash_args->path = argv[i];
			printf("getting path: {%s}\n", hash_args->path);
			hash_args->state = GET_NAME;
		}
		else if (argv[i][0] == '-' && hash_args->state == GET_OPT)
		{
			printf("argv[%d]: {%s}\n", i, argv[i]);
			if (!get_hash_opt(argv[i], hash_args))
			{
				ft_memdel((void*)&hash_args);
				return (NULL);
			}
		}
		//printf("hash_args->state: %d\n", hash_args->state);
	}
	return (hash_args);
}

int		hash_builtin(t_hashmap *hashmap, int argc, char **argv, char **env)
{
	t_hash_args	*hash_args;

	printf("___HASH_BUILTIN___\n");
	//hash [-lr] [-p pathname] [-dt] [name ...]
	if (argc == 1)
	{
		print_hashmap(hashmap);
		return (0);
	}
	if (!(hash_args = get_hash_args(argc, argv)))
		return (1);
	//
	printf("END:\nopt={");
	print_bits(hash_args->opt);
	printf("}\npath: {%s}\n", hash_args->path);
	//
	printf("___EXEC___\n");
	if (hash_args->opt & O_R)
		reset_hashmap(&hashmap);
	if (hash_args->opt & O_D && name_index)//	d > l (if NAME)
		//pop each args from name_index
	if (!name_index)
	{
		if (hash_args->opt & O_L)
			print_hashmap_l(hashmap);//, hash_args);
		else if (hash_args->opt & O_D)
			print_hashmap(hashmap);
	}//else (if name_index)
	return (1);
}
