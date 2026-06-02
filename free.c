/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:39:11 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 13:39:11 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

void	free_config(t_config config)
{
	if (config.no)
		free(config.no);
	if (config.ea)
		free(config.ea);
	if (config.so)
		free(config.so);
	if (config.we)
		free(config.we);
}

void	free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->max_height)
		free(map->map[i++]);
	free(map->map);
}

void	free_parse_info(t_info *info, char *str)
{
	if (str)
		free(str);
	free_config(info->config);
	free_map(&info->map_info);
	get_next_line(-1);
	exit(1);
}
