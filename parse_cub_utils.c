#include "map.h"

void	*ft_realloc(void *ptr, size_t new_size)
{
	(void)ptr;
	(void)new_size;

	//  実装してください。

	return (NULL);
}

bool	ft_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

void	put_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	exit(1);
}
