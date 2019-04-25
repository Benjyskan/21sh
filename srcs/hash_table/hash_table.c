#include "hash_table.h"

//create a single hash item
static t_hash_item	*create_hash_item(const char *key, const char *value)
{
	t_hash_item	*new_item;

	if (!(new_item = (t_hash_item*)malloc(sizeof(*new_item))))
		return (NULL);//ERROR_MEM;
	if (!(new_item->key = ft_strdup(key)))
	{
		ft_memdel((void*)&new_item);
		return (NULL);//ERROR_MEM;
	}
	if (!(new_item->value = ft_strdup(value)))
	{
		ft_memdel((void*)&new_item->key);
		ft_memdel((void*)&new_item);
		return (NULL);//ERROR_MEM;
	}
	new_item->next = NULL;
	return (new_item);
}

//delete a single hash item
static void		delete_hash_item(t_hash_item *item)
{
	ft_memdel((void*)&item->key);
	ft_memdel((void*)&item->value);
	ft_memdel((void*)&item);
}

//delete thw whole hash table
void		delete_hash_table(t_hash_table *hash_table)
{
	int	i;

	i = -1;
	while (++i < hash_table->size)
	{
		if (hash_table->items[i])
			delete_hash_item(hash_table->items[i]);
	}
	ft_memdel((void*)&hash_table->items);
	ft_memdel((void*)&hash_table);
}

//init an empty hash table of size size (size should be primary ?)
t_hash_table	*init_hash_table(size_t size)
{
	t_hash_table	*new_table;
	int				i;

	if (!(new_table = (t_hash_table*)malloc(sizeof(*new_table))))
		return (NULL);//ERROR_MEM;
	if (!(new_table->items = (t_hash_item**)malloc(sizeof(t_hash_item) * size)))
	{
		ft_memdel((void*)&new_table);
		return (NULL);//ERROR_MEM;
	}
	new_table->size = size;
	new_table->count = 0;
	i = -1;
	while (++i < new_table->size)
		new_table->items[i] = NULL;
	return (new_table);
}
