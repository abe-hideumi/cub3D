/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:39:44 by knomura           #+#    #+#             */
/*   Updated: 2026/06/04 11:21:06 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

static bool	is_config_complete(t_config config)
{
	return (config.no && config.so && config.we && config.ea
		&& config.f != -1 && config.c != -1);
}

static int	parse_config(char *line, t_info *info)
{
	while (ft_is_space(*line))
		line++;
	if (*line == '\n')
		return (0);
	if (!ft_strncmp("NO ", line, 3))
		return (parse_texture_img(&info->config.no, line), 0);
	if (!ft_strncmp("SO ", line, 3))
		return (parse_texture_img(&info->config.so, line), 0);
	if (!ft_strncmp("WE ", line, 3))
		return (parse_texture_img(&info->config.we, line), 0);
	if (!ft_strncmp("EA ", line, 3))
		return (parse_texture_img(&info->config.ea, line), 0);
	if (!ft_strncmp("F ", line, 2))
		return (parse_texture_color(&info->config.f, line), 0);
	if (!ft_strncmp("C ", line, 2))
		return (parse_texture_color(&info->config.c, line), 0);
	if (!is_config_complete(info->config))
		put_error_free("INVALID OR MISSING CONFIG", info, NULL);
	return (1);
}

static void	read_map(char *line, t_info *info)
{
	char	**tmp;
	size_t	len;

	tmp = ft_realloc(info->map_info.map, sizeof(char *)
			* (info->map_info.max_height + 2));
	if (tmp == NULL)
		put_error_free("ft_realloc Failed", info, line);
	info->map_info.map = tmp;
	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[--len] = '\0';
	if (info->map_info.max_width < (int)len)
		info->map_info.max_width = (int)len;
	info->map_info.map[info->map_info.max_height] = ft_strdup(line);
	if (!info->map_info.map[info->map_info.max_height])
		put_error_free("Malloc failed", info, line);
	info->map_info.max_height++;
	info->map_info.map[info->map_info.max_height] = NULL;
}

void	read_file(char *file, t_info *info)
{
	int		fd;
	char	*line;
	int		in_map;

	in_map = 0;
	fd = open(file, O_RDONLY);
	if (fd < 0)
		put_error_free("Cannot open file", info, NULL);
	line = get_next_line(fd);
	while (line)
	{
		if (!in_map)
			in_map = parse_config(line, info);
		if (in_map)
			read_map(line, info);
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}
