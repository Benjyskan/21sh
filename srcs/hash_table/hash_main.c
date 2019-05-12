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
			print_usage();
			//dprintf(2, "hash [-lr] [-p pathname] [-d] [name ...]\n");//no 't'
			return (0);
		}
	}
	return (1);
}

static t_hash_args	*get_hash_args(int argc, char **argv)
{
	t_hash_args	*hash_args;
	int			i;

	printf("(get_hash_args)ICICICICICICIC\n");
	hash_args = init_hash_args();
	i = 0;
	while (++i < argc)
	{
		if (argv[i][0] != '-' && hash_args->state == GET_OPT)
		{
			hash_args->state = GET_NAME;
			//if (!hash_args->name_index)
			//	hash_args->name_index = i;
		}
		if (hash_args->state == GET_NAME && !hash_args->name_index)
		{
			printf("(get_hash_args)getting name: {%s}\n", argv[i]);
			hash_args->name_index = i;
			hash_args->state = GET_DONE;
			printf("(get_hash_args)with name_index: {%d}\n", hash_args->name_index);
		}
		else if (hash_args->state == GET_PATH)
		{
			hash_args->path = argv[i];
			printf("(get_hash_args)getting path: {%s}\n", hash_args->path);
			hash_args->state = GET_NAME;
		}
		else if (argv[i][0] == '-' && hash_args->state == GET_OPT)
		{
			printf("(get_hash_args)argv[%d]: {%s}\n", i, argv[i]);
			if (!get_hash_opt(argv[i], hash_args))
			{
				ft_memdel((void*)&hash_args);
				return (NULL);
			}
		}
		//printf("hash_args->state: %d\n", hash_args->state);
	}
	if (hash_args->state == GET_PATH)
	{
		print_usage();
		ft_memdel((void*)&hash_args);
		return (NULL);
	}
	return (hash_args);
}

static void	add_each_name(t_hashmap **hashmap, t_hash_args *hash_args, int argc, char **argv)
{
	int		i;
	char	*value;

	i = hash_args->name_index - 1;
	while (++i < argc)
	{
		//value = search in path;
		add_to_hashmap(argv[i], value, hashmap);
	}
}

static void	add_each_name_with_path(t_hashmap **hashmap, t_hash_args *hash_args, int argc, char **argv)
{
	int		i;

	i = hash_args->name_index - 1;
	while (++i < argc)
	{
		add_to_hashmap(argv[i], hash_args->path, hashmap);
	}
}

static void	pop_each_name(t_hashmap **hashmap, t_hash_args *hash_args, int argc, char **argv)
{
	int	i;

	i = hash_args->name_index - 1;
	while (++i < argc)
	{
		pop_hashmap_item(argv[i], *hashmap);//make pop() take **hashmap ??
	}
}

static void	hash_builtin_print(t_hashmap *hashmap, t_hash_args *hash_args, int argc, char **argv)//TODO change so L print only args(starting @ name_index)
{
	int	i;

	if (hash_args->opt & O_L)
	{
		if (!hash_args->name_index)
			print_hashmap_l(hashmap);//TODO:, hash_args);
		else
			print_hashmap_l_args(hashmap, hash_args, argc, argv);
	}
	else
		print_hashmap(hashmap);
}

//L only matter when printing
//make 'hash -l ls' same as 'hash -t ls'
//p>d (if name)
int			hash_builtin(t_hashmap **hashmap, int argc, char **argv, char **env)
{
	t_hash_args	*hash_args;

	printf("___HASH_BUILTIN___\n");
	//hash [-lr] [-p pathname] [-dt] [name ...]
	//
	(void)env;
	if (argc == 1)
	{
		print_hashmap(*hashmap);
		return (0);
	}
	if (!(hash_args = get_hash_args(argc, argv)))
		return (1);
	//
	printf("END:\nopt={");
	printf("RDL: ");
	print_bits(hash_args->opt);
	printf("}\npath: {%s}\nname_index: %d\n", hash_args->path,
			hash_args->name_index);
	//
	printf("___EXEC___\n");
	if (hash_args->opt & O_R)//priority
		reset_hashmap(hashmap);
	if (hash_args->path)
	{
		if (hash_args->name_index)
			add_each_name_with_path(hashmap, hash_args, argc, argv);
		else
			hash_builtin_print(*hashmap, hash_args, argc, argv);//print//mv down
	}
	else if (hash_args->opt & O_D)
	{
		if (hash_args->name_index)
			pop_each_name(hashmap, hash_args, argc, argv);
		else
			hash_builtin_print(*hashmap, hash_args, argc, argv);//print//mv down
	}
	else if (!hash_args->opt && hash_args->name_index)//test !opt
	{
		add_each_name(hashmap, hash_args, argc, argv);
	}
	else
		hash_builtin_print(*hashmap, hash_args, argc, argv);//print
	return (1);

	//old////////////////
	/*
	if (hash_args->path && hash_args->name_index)
	{
		//add each args with that path//seems good
	}
	else if (hash_args->opt & O_D && hash_args->name_index)//	p>d(if NAME)
	{
		printf("pop args starting at %d\n", hash_args->name_index);
		//pop each args from name_index
	}
	if (!hash_args->name_index)
	{
		hash_builtin_print(*hashmap, hash_args);
		//if (hash_args->opt & O_L)
		//	print_hashmap_l(*hashmap);//TODO:, hash_args) to print each args (different from bash)
		//else if (hash_args->opt & O_D)
		//	print_hashmap(*hashmap);
	}
	else //(if hash_args->name_index)
	{
		//if L
		//or D
	}
	return (1);
	*/
}
