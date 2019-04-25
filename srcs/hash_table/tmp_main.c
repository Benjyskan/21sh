#include "hash_table.h"

int		main(void)
{
	t_hash_table	*hash_table;

	if (!(hash_table = init_hash_table(7)))
	{
		dprintf(2, "init_hash_table returned NULL\n");
		return (1);
	}
	delete_hash_table(hash_table);
	printf("Cool\n");
	return (0);
}
