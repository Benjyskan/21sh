#include "hashmap.h"

int		main(int argc, char **argv, char **env)
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
	add_to_hashmap("20", "/bin/bonjour",&hashmap);
	add_to_hashmap("21", "/bin/bonjour",&hashmap);
	add_to_hashmap("22", "/bin/bonjour",&hashmap);
	add_to_hashmap("ls", "/bin/ls",&hashmap);
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
	//hashmap = resize_down_hashmap(hashmap);
	//hashmap = resize_down_hashmap(hashmap);
	//hashmap = resize_down_hashmap(hashmap);
	ft_printf("_________HERE_______________\n");
	print_hashmap(hashmap);
	//pop_hashmap_item("7", hashmap);
	pop_hashmap_item("20", hashmap);
	pop_hashmap_item("16", hashmap);
	//pop_hashmap_item("3", hashmap);
	print_hashmap(hashmap);
	//
	const char	*path;
	if ((path = check_hashmap("ls", hashmap, HASH_EXEC)))
		printf("exec ls @ %s\n", path);
	else
		printf("ls not found in hashmap\n");
	print_hashmap(hashmap);
	//
	hash_builtin(hashmap, argc, argv, env);
	//


	delete_hashmap(hashmap);
	return (0);
	printf("check for '14': {%s}\n", check_hashmap("14", hashmap, HASH_CHECK));
	reset_hashmap(&hashmap);
	printf("check for '14': {%s}\n", check_hashmap("14", hashmap, HASH_CHECK));
	add_to_hashmap("ls", "/bin/ls",&hashmap);
	add_to_hashmap("ls", "/bin/lsa",&hashmap);
	print_hashmap(hashmap);





	//
	ft_printf("post delete\n");
	delete_hashmap(hashmap);
	ft_printf("Cool\n");
	return (0);
}
