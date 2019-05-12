#ifndef hashmap_H
# define hashmap_H

#include "tosh.h"
#include "libft.h"

#define INIT_HASH_SIZE 7// should be prime
#define MAX_HASHMAP_COLLISION 3
#define TRUE 1
#define FALSE 0

typedef struct	s_hash_item
{
	char				*key;
	char				*value;
	size_t				count;
	struct s_hash_item	*next;
}				t_hash_item;

typedef struct	s_hashmap
{
	size_t		size;
	t_hash_item	**items;

}				t_hashmap;

/*
** t_hashopt
** give check_hashmap() intructions for modifying the count
*/

typedef enum	e_hashopt
{
	HASH_CHECK,
	HASH_EXEC,
	HASH_RESET
}				t_hashopt;

void			delete_hashmap(t_hashmap *hashmap);
t_bool			add_to_hashmap(char *key, char *value, t_hashmap **hashmap);
unsigned int	hashfun(const char *input);
const char		*check_hashmap(const char *key, t_hashmap *hashmap, t_hashopt opt);
//unsigned int	get_hashmap_index(const char *key, t_hashmap *hashmap);
/*
** hashmap_print.c
*/
void			print_hashmap(t_hashmap *hashmap);
void			print_hashmap_l(t_hashmap *hashmap);
void			print_usage(void);

/*
** hashmap_alloc.c
*/
t_hash_item		*create_new_item(const char *key, const char *value);
t_hashmap		*init_hashmap(size_t size);
t_hashmap		*resize_up_hashmap(t_hashmap *old_map);
t_hashmap		*resize_down_hashmap(t_hashmap *old_map);
void			cpy_hashmap(t_hashmap *old_map, t_hashmap **new_map);

/*
** hashmap_delete.c
*/
//static void		delete_hashmap_item(t_hash_item *item);
void			delete_hashmap(t_hashmap *hashmap);
void			replace_item(t_hash_item *item, const char *value);
t_bool			pop_hashmap_item(const char *key, t_hashmap *hashmap);
t_bool			reset_hashmap(t_hashmap **hashmap);

/*
** prime.c
*/
unsigned int	find_next_prime(unsigned int nb);
unsigned int	find_prev_prime(unsigned int nb);

/*
** hash_main.c
*/
int				hash_builtin(t_hashmap **hashmap, int argc, char **argv, char **env);
#endif
