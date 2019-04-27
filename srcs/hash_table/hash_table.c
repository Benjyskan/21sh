#include "hash_table.h"

//create a single hash item //useless ?
static t_hash_item	*create_new_item(const char *key, const char *value)
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
	while (++i < (int)hash_table->size)
	{
		if (hash_table->items[i])
			delete_hash_item(hash_table->items[i]);
	}
	ft_memdel((void*)&hash_table->items);
	ft_memdel((void*)&hash_table);
}

unsigned int	get_hashmap_index(const char *key, t_hash_table *hashmap)
{
	//return (hashfun(key) % hashmap->size);//so useless
	unsigned int	index;

	index = hashfun(key) % hashmap->size;
	return (index);
}

void		replace_item(t_hash_item *item, const char *value)
{
	ft_memdel((void*)&item->value);
	if (!(item->value = ft_strdup(value)))
		return ;//ERROR_MEM;
}

t_bool		add_to_hashmap(char *key, char *value, t_hash_table *hashmap)
{
	unsigned int	index;
	t_hash_item		*item_probe;
	t_hash_item		*prev_probe;

	index = hashfun(key) % hashmap->size;
	item_probe = hashmap->items[index];
	prev_probe = NULL;
	while (item_probe && ft_strcmp(key, item_probe->key))
	{
		prev_probe = item_probe;
		item_probe = item_probe->next;
	}
	if (item_probe)//	item found
	{
		replace_item(item_probe, value);//	protect
		return (1);
	}
	else//	item not found
	{
		if (!prev_probe)//	no linked item
		{
			if (!(hashmap->items[index] = create_new_item(key, value)))
				return (0);//ERROR_MEM;
		}
		else if (!(prev_probe->next = create_new_item(key, value)))//	i'm at the end of list
			return (0);//ERROR_MEM;
		return (1);
	}
}

//return value of key or NULL
const char	*check_hashmap(const char *key, t_hash_table *hashmap)
{
	unsigned int	index;
	t_hash_item		*item_probe;

	//item_probe = hashmap->items[hashfun(key) % hashmap->size];//no need for index
	index = hashfun(key) % hashmap->size;
	item_probe = hashmap->items[index];
	while (item_probe)
	{
		if (!ft_strcmp(key, item_probe->key))
			return (item_probe->value);
		item_probe = item_probe->next;
	}
	return (NULL);
}

//init an empty hash table of size size (size should be primary ?)
t_hash_table	*init_hash_table(size_t size)
{
	t_hash_table	*new_table;
	int				i;

	if (!(new_table = (t_hash_table*)malloc(sizeof(*new_table))))
		return (NULL);//ERROR_MEM;
	if (!(new_table->items
				= (t_hash_item**)malloc(sizeof(t_hash_item*) * size)))
	{
		ft_memdel((void*)&new_table);
		return (NULL);//ERROR_MEM;
	}
	new_table->size = size;
	new_table->count = 0;
	i = -1;
	while (++i < (int)new_table->size)
		new_table->items[i] = NULL;
	return (new_table);
}
