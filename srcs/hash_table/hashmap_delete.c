#include "hashmap.h"

static void		delete_hashmap_item(t_hash_item *item)
{
	ft_memdel((void*)&item->key);
	ft_memdel((void*)&item->value);
	ft_memdel((void*)&item);
}

/*
** delete_hashmap
** free the whole hashmap
*/

void		delete_hashmap(t_hashmap *hashmap)
{
	int			i;
	t_hash_item	*item_probe;
	t_hash_item	*prev_probe;

	i = -1;
	while (++i < (int)hashmap->size)
	{
		if (hashmap->items[i])
		{
			item_probe = hashmap->items[i];
			while (item_probe)
			{
				prev_probe = item_probe;
				item_probe = item_probe->next;
				delete_hashmap_item(prev_probe);
			}
		}
	}
	ft_memdel((void*)&hashmap->items);
	ft_memdel((void*)&hashmap);
}

/*
** replace item
** substitute the given item value by a new one
*/

void		replace_item(t_hash_item *item, const char *value)
{
	ft_memdel((void*)&item->value);
	if (!(item->value = ft_strdup(value)))
		return ;//ERROR_MEM;
}
