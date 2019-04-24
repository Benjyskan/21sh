#include "reader.h"
#include "tosh.h"

size_t	ft_printable_len(const char *s1)
{
	size_t	i;
	size_t	res;

	i = 0;
	res = 0;
	while (s1[i])
	{
		if (ft_isprint(s1[i]) || s1[i] == '\n')
			res++;
		i++;
	}
	return (res);
}

char	*ft_strdup_print(const char *s1)
{
	char	*res;
	size_t	len;
	size_t	i;

	i = 0;
	if (!(res = ft_strnew(ft_printable_len(s1))))
		return (NULL);
	i = 0;
	len = 0;
	while (s1[i])
	{
		if (ft_isprint(s1[i]))
		{
			res[len] = s1[i];
			len++;
		}
		i++;
	}
	res[i] = 0;
	return (res);
}

void	insert_str(t_cmd_struct *cmd_struct, const char *buf,
		size_t printable_len)
{
	char	*tmp;

	if (!(tmp = ft_strdup_print(&cmd_struct->append_txt[cmd_struct->tracker])))
		ERROR_MEM;
	ft_strcpy(&cmd_struct->append_txt[cmd_struct->tracker + printable_len],
			tmp);
	ft_strncpy(&cmd_struct->append_txt[cmd_struct->tracker], buf, printable_len);
	ft_memdel((void*)&tmp);
}
