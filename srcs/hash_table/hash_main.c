#include "hashmap.h"

int		hash_builtin(t_hashmap *hashmap, int argc, char **argv, char **env)
{
	//hash [-lr] [-p pathname] [-dt] [name ...]
	if (argc == 1)
	{
		print_hashmap(hashmap);
		return (EXIT_SUCCES);//bof
	}

}
