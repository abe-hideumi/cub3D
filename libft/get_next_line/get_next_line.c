/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 01:16:00 by knomura           #+#    #+#             */
/*   Updated: 2026/05/09 19:36:56 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

char	*clean_stash(char *stash)
{
	size_t	i;
	size_t	j;
	char	*new_stash;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
	{
		free(stash);
		return (NULL);
	}
	i++;
	new_stash = malloc(ft_gnl_strlen(stash + i) + 1);
	if (!new_stash)
		return (NULL);
	j = 0;
	while (stash[i])
		new_stash[j++] = stash[i++];
	new_stash[j] = '\0';
	free(stash);
	return (new_stash);
}

char	*extract_line(char *stash)
{
	size_t	i;
	size_t	j;
	char	*line;

	if (!stash || stash[0] == '\0')
		return (NULL);
	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (stash[i] == '\n')
		i++;
	line = malloc(i + 1);
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = stash[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*read_and_stash(int fd, char *stash)
{
	char	*buf;
	ssize_t	bytes_read;
	char	*tmp;

	bytes_read = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while ((ft_gnl_strchr(stash, '\n') == NULL) && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buf), NULL);
		buf[bytes_read] = '\0';
		tmp = stash;
		stash = ft_gnl_strjoin(stash, buf);
		free(tmp);
		if (!stash)
			return (free(buf), NULL);
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char		*stash;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(stash), stash = NULL, NULL);
	if (stash == NULL)
		stash = ft_gnl_strdup("");
	stash = read_and_stash(fd, stash);
	if (stash == NULL)
		return (NULL);
	line = extract_line(stash);
	stash = clean_stash(stash);
	if (line == NULL && stash != NULL)
	{
		free(stash);
		stash = NULL;
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	int		i;

// 	fd = 0;
// 	// fd = open("sample.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	i = 0;
// 	printf("%d\n",fd);
// 	while (i < 3)
// 	{
// 		line = get_next_line(fd);
// 		printf("%s", line);
// 		free(line);
// 		i++;
// 	}
// 	close(fd);
// 	return (0);
// }
