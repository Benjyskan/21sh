#include "hashmap.h"

int		main(void)
{
	t_hashmap	*hashmap;

	//if (!(hashmap = init_hashmap(INIT_HASH_SIZE)))
	if (!(hashmap = init_hashmap(3)))
	{
		ft_dprintf(2, "init_hashmap returned NULL\n");
		return (1);
	}
	add_to_hashmap("1", "/bin/ls",&hashmap);
	add_to_hashmap("2", "/bin/lt",&hashmap);
	add_to_hashmap("3", "/bin/cat",&hashmap);
	add_to_hashmap("4", "/bin/bonsoir",&hashmap);
	add_to_hashmap("5", "/bin/bonjour",&hashmap);
	add_to_hashmap("6", "/bin/bonjour",&hashmap);
	add_to_hashmap("7", "/bin/bonjour",&hashmap);
	add_to_hashmap("8", "/bin/bonjour",&hashmap);
	add_to_hashmap("9", "/bin/bonjour",&hashmap);
	add_to_hashmap("10", "/bin/bonjour",&hashmap);
	add_to_hashmap("11", "/bin/bonjour",&hashmap);
	add_to_hashmap("12", "/bin/bonjour",&hashmap);
	add_to_hashmap("13", "/bin/bonjour",&hashmap);
	add_to_hashmap("14", "/bin/NOP",&hashmap);
	add_to_hashmap("15", "/bin/bonjour",&hashmap);
	add_to_hashmap("16", "/bin/bonjour",&hashmap);
	add_to_hashmap("17", "/bin/bonjour",&hashmap);
	add_to_hashmap("18", "/bin/bonjour",&hashmap);
	add_to_hashmap("19", "/bin/bonjour",&hashmap);
	printf("################################\n");
	print_hashmap(hashmap);
	printf("################################\n");
	//t_hash_item *item_probe = hashmap->items[hashfun("ls") % hashmap->size];
	//while (item_probe)
	//{
	//	ft_printf("probe: {%s}\n", item_probe->value);
	//	item_probe = item_probe->next;
	//}
	ft_printf("____________________________\n");
	print_hashmap(hashmap);
	add_to_hashmap("19", "NEWNEW", &hashmap);
	print_hashmap(hashmap);
	ft_printf("_________post_resize_down___\n");
	hashmap = resize_down_hashmap(hashmap);
	hashmap = resize_down_hashmap(hashmap);
	ft_printf("____kajhdfgkjshdfgkjh_______\n");
	print_hashmap(hashmap);






	//
	ft_printf("post delete\n");
	delete_hashmap(hashmap);
	ft_printf("Cool\n");
	return (0);
}
