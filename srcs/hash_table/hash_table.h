#ifndef HASH_TABLE_H
# define HASH_TABLE_H

#include "tosh.h"
#include "libft.h"

#define INIT_HASH_SIZE 7// should be prime

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
t_bool			add_to_hashmap(char *key, char *value, t_hash_table *hashmap);
unsigned int	hashfun(const char *input);
const char		*check_hashmap(const char *key, t_hash_table *hashmap);
#endif
