/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:39:33 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 13:49:45 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static void	check_extenstion(char *map_name)
{
	size_t	len;

	len = ft_strlen(map_name);
	if (len < 5 || ft_strncmp(".cub", map_name + len - 4, 4))
		printf("Invalid file extension. Must be .cub\n");
}

void	parse_cub_file(char *file, t_info *info)
{
	check_extenstion(file);
	info->player_dir = 0;
	info->config = (t_config){NULL, NULL, NULL, NULL, -1, -1};
	info->map_info = (t_map){0};
	info->map_info.map = malloc(sizeof(char *) * 1);
	if (info->map_info.map == NULL)
		put_error_free("malloc failed", info, NULL);
	read_file(file, info);
	validate_map_chars(info);
	validate_map_enclosed(info);
}
