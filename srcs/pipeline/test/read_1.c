#include <unistd.h>
#include <stdio.h>

int	main(void)
{
	char c;

	while (read(4, &c, 1) > 0)
		printf("READ: %d\n", c);
	return (0);
}
