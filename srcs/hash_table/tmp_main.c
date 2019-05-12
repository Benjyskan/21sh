#include "hashmap.h"

int		main(int argc, char **argv, char **env)
{
	t_hashmap	*hashmap;

	(void)env;
	//if (!(hashmap = init_hashmap(INIT_HASH_SIZE)))
	if (!(hashmap = init_hashmap(3)))
	{
		ft_dprintf(2, "init_hashmap returned NULL\n");
		return (1);
	}
	add_to_hashmap("1", "/bin/1",&hashmap);
	add_to_hashmap("2", "/bin/2",&hashmap);
	add_to_hashmap("3", "/bin/3",&hashmap);
	add_to_hashmap("4", "/bin/4",&hashmap);
	add_to_hashmap("5", "/bin/5",&hashmap);
	add_to_hashmap("6", "/bin/6",&hashmap);
	add_to_hashmap("7", "/bin/7",&hashmap);
	add_to_hashmap("8", "/bin/8",&hashmap);
	add_to_hashmap("9", "/bin/9",&hashmap);
	add_to_hashmap("10", "/bin/10",&hashmap);
	add_to_hashmap("11", "/bin/11",&hashmap);
	add_to_hashmap("12", "/bin/12",&hashmap);
	add_to_hashmap("13", "/bin/13",&hashmap);
	add_to_hashmap("14", "/bin/14",&hashmap);
	add_to_hashmap("15", "/bin/15",&hashmap);
	add_to_hashmap("16", "/bin/16",&hashmap);
	add_to_hashmap("17", "/bin/17",&hashmap);
	add_to_hashmap("18", "/bin/18",&hashmap);
	add_to_hashmap("19", "/bin/19",&hashmap);
	add_to_hashmap("20", "/bin/20",&hashmap);
	add_to_hashmap("21", "/bin/21",&hashmap);
	add_to_hashmap("22", "/bin/22",&hashmap);
	add_to_hashmap("ls", "/bin/ls",&hashmap);
	printf("################################\n");
	print_hashmap(hashmap);
	printf("################################\n");
	//ft_printf("_________post_resize_down___\n");
	//hashmap = resize_down_hashmap(hashmap);
	//hashmap = resize_down_hashmap(hashmap);
	//hashmap = resize_down_hashmap(hashmap);
	ft_printf("_________poping_20_16_______\n");
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
	printf("(main)hash_builtin\n");
	hash_builtin(&hashmap, argc, argv, env);
	printf("(main)hash_builtin END\n");
	//


	print_hashmap(hashmap);
	printf("(main)delete_hashmap\n");
	delete_hashmap(hashmap);
	return (0);
	//
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
