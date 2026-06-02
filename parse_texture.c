/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_texture.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:39:40 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 13:53:50 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

int	parse_texture_img(char **field, char *line)
{
	size_t	len;
	int		fd;

	if (*field != NULL)
		return (put_error("Invalid config: duplicate identifier"), -1);
	line += 3;
	while (ft_is_space(*line))
		line++;
	if (*line == '\0' || *line == '\n')
		return (put_error("Texture path is empty"), -1);
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || ft_is_space(line[len - 1])))
		len--;
	if (len == 0)
		return (put_error("Texture path is empty"), -1);
	*field = ft_substr(line, 0, len);
	if (*field == NULL)
		return (put_error("Malloc failed"), -1);
	fd = open(*field, O_RDONLY);
	if (fd < 0)
		return (put_error("Texture file not found"), -1);
	close(fd);
	return (0);
}

static int	validate_rgb_format(char *line)
{
	int	comma;

	comma = 0;
	if (!ft_isdigit(*line))
		return (-1);
	while (*line)
	{
		if (*line == ',')
		{
			comma++;
			if (!ft_isdigit(*(line + 1)))
				return (-1);
		}
		else if (!ft_isdigit(*line))
			return (-1);
		line++;
	}
	if (comma != 2)
		return (-1);
	return (0);
}

static int	ft_atoi_rgb(char **s)
{
	int	n;

	n = 0;
	while (ft_isdigit(**s))
	{
		n = n * 10 + (**s - '0');
		(*s)++;
	}
	if (**s == ',')
		(*s)++;
	if (n < 0 || n > 255)
		return (put_error("Color code invalid 0 ~ 255"), -1);
	return (n);
}

static int	parse_rgb_to_int(char *line)
{
	int	rgb[3];

	if (validate_rgb_format(line))
		return (put_error("Invalid color format"), -1);
	rgb[0] = ft_atoi_rgb(&line);
	rgb[1] = ft_atoi_rgb(&line);
	rgb[2] = ft_atoi_rgb(&line);
	if (rgb[0] == -1 || rgb[1] == -1 || rgb[2] == -1)
		return (-1);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

int	parse_texture_color(int *field, char *line)
{
	size_t	len;
	int		result;

	if (*field != -1)
		return (put_error("Invalid config: duplicate identifier"), -1);
	line += 2;
	while (ft_is_space(*line))
		line++;
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || ft_is_space(line[len - 1])))
		line[--len] = '\0';
	if (len == 0)
		return (put_error("Color value is empty"), -1);
	result = parse_rgb_to_int(line);
	if (result == -1)
		return (-1);
	*field = result;
	return (0);
}
