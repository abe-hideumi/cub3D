/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_map_enclosed.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:39:55 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 18:39:53 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static int	check_single_direction(char **map, int x, int y)
{
	if (x < 0 || y < 0 || !map[y]
		|| x >= (int)ft_strlen(map[y]) || map[y][x] == ' ')
		return (1);
	return (0);
}

static bool	check_all_direction(char **map, int x, int y)
{
	int	err;

	err = 0;
	err = check_single_direction(map, x + 1, y);
	err += check_single_direction(map, x - 1, y);
	err += check_single_direction(map, x, y + 1);
	err += check_single_direction(map, x, y - 1);
	return (err);
}

void	validate_map_enclosed(t_info *info)
{
	char	**map;
	int		x;
	int		y;
	int		len;

	map = info->map_info.map;
	y = 0;
	while (y < info->map_info.max_height)
	{
		x = 0;
		len = ft_strlen(map[y]);
		while (x < len)
		{
			if (map[y][x] == 'P' || map[y][x] == '0')
				if (check_all_direction(map, x, y))
					put_error_free("Map not closed", info, NULL);
			x++;
		}
		y++;
	}
}
