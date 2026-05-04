#include <stdio.h>

typedef struct s_map
{
	char		**map;
	int			player_direction;
	size_t		width;
	size_t		height;
}				t_map;


void	check_extenstion(char *map_name)
{
	size_t	len;

	len = ft_strlen(map_name);
	if (len < 5 || ft_strncmp(".cub", map_name + len - 4, 4))
		put_error_free_close(-1, NULL, "Invalid file extension. Must be .cub\n",
			NULL);
}

void parse_map(char *file)
{
	check_extenstion(file);




}