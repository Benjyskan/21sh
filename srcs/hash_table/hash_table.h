#ifndef HASH_TABLE_H
# define HASH_TABLE_H

#include "tosh.h"
#include "libft.h"

typedef struct	s_hash_item
{
	char				*key;
	char				*value;
	struct s_hash_item	*next;
}				t_hash_item;

typedef struct	s_hash_table
{
	size_t		size;
	size_t		count;
	t_hash_item	**items;

}				t_hash_table;

t_hash_table	*init_hash_table(size_t size);
void			delete_hash_table(t_hash_table *hash_table);
#endif
