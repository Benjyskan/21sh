#include "hashmap.h"

/*
void	print_hashmap(t_hashmap *hashmap)//debug
{
	int			i;
	t_hash_item	*item_probe;

	printf("hashmap->size = %zu\n", hashmap->size);
	ft_printf("index\thits\tcommand=path\n");
	i = -1;
	while (++i < hashmap->size)
	{
		item_probe = hashmap->items[i];
		while (item_probe)
		{
			printf("%d\t%lu\t{%s}={%s}\n", i, item_probe->count, item_probe->key, item_probe->value);
			item_probe = item_probe->next;
		}
	}
}
*/

void	print_hashmap(t_hashmap *hashmap)//REAL
{
	int			i;
	t_hash_item	*item_probe;

	ft_printf("hits\tcommand\n");
	i = -1;
	while (++i < (int)hashmap->size)
	{
		printf("(print_hashmap) i: %d, size: %zu\n", i, hashmap->size);
		item_probe = hashmap->items[i];
		while (item_probe)
		{
			ft_printf("%4d\t%s\n", item_probe->count, item_probe->value);
			//printf("%4d\t%s\n", 14000, item_probe->value);
			item_probe = item_probe->next;
		}
	}
}

void	print_hashmap_l_args(t_hashmap *hashmap, t_hash_args *hash_args, int argc, char **argv)
{
	int			i;
	const char	*value;

	i = hash_args->name_index - 1;
	while (++i < argc)
	{
		if ((value = check_hashmap(argv[i], hashmap, HASH_CHECK)))
			ft_printf("hash -p %s %s\n", value, argv[i]);
		else
			dprintf(2, "hash: %s wasn't found\n", argv[i]);
	}
}

void	print_hashmap_l(t_hashmap *hashmap)
//void	print_hashmap_l(t_hashmap *hashmap, t_hash_args *hash_args, int argc,
//		char ** argv);
{
	int			i;
	t_hash_item	*item_probe;
	//t_bool is_empty;//to print hash table empty

	i = -1;
	while (++i < (int)hashmap->size)
	{
		item_probe = hashmap->items[i];
		while (item_probe)
		{
			ft_printf("hash -p %s %s\n", item_probe->value, item_probe->key);
			item_probe = item_probe->next;
		}
	}
}

void	print_usage(void)
{
	dprintf(2, "hash [-lr] [-p pathname] [-d] [name ...]\n");//no 't'
}
