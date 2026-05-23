#include "map.h"

void	parse_texture_img(char **field, char *line)
{
	size_t	len;
	int		fd;

	if (*field != NULL)
		put_error("Invalid config: duplicate identifier");
	line += 3;
	while (ft_is_space(*line))
		line++;
	if (*line == '\0' || *line == '\n')
		put_error("Texture path is empty");
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || ft_is_space(line[len - 1])))
		len--;
	if (len == 0)
		put_error("Texture path is empty");
	*field = ft_substr(line, 0, len);
	if (*field == NULL)
		put_error("Malloc failed");
	fd = open(*field, O_RDONLY);
	if (fd < 0)
		put_error("Texture file not found");
	close(fd);
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
		put_error("Color code invalid 0 ~ 255");
	return (n);
}

static int	parse_rgb_to_int(char *line)
{
	int	rgb[3];

	if (validate_rgb_format(line))
		put_error("Invalid color format");
	rgb[0] = ft_atoi_rgb(&line);
	rgb[1] = ft_atoi_rgb(&line);
	rgb[2] = ft_atoi_rgb(&line);
	return (rgb[0] << 16 | rgb[1] << 8 | rgb[2]);
}

void	parse_texture_color(int *field, char *line)
{
	size_t	len;

	if (*field != -1)
		put_error("Invalid config: duplicate identifier");
	line += 2;
	while (ft_is_space(*line))
		line++;
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == '\n' || ft_is_space(line[len - 1])))
		line[--len] = '\0';
	if (len == 0)
		put_error("Color value is empty");
	*field = parse_rgb_to_int(line);
}


