/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/02 14:13:56 by knomura           #+#    #+#             */
/*   Updated: 2025/06/02 17:04:08 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>
#include <limits.h>

char	*clean_stash(char *stash)
{
	char	*new_stash;
	size_t	i;
	size_t	j;

	i = 0;
	while (stash[i] && stash[i] != '\n')
		i++;
	if (!stash[i])
		return (free(stash), NULL);
	i++;
	new_stash = malloc(ft_strlen(stash + i) + 1);
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
	char	*line;
	size_t	i;
	size_t	j;

	if (stash == NULL || stash[0] == '\0')
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
	ssize_t	bytes_read;
	char	*buf;
	char	*tmp;

	bytes_read = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (ft_strchr(stash, '\n') == NULL && bytes_read != 0)
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buf), NULL);
		buf[bytes_read] = '\0';
		tmp = stash;
		stash = ft_strjoin(stash, buf);
		free(tmp);
		if (!stash)
			return (free(buf), NULL);
	}
	free(buf);
	return (stash);
}

char	*get_next_line(int fd)
{
	static char	*stash[OPEN_MAX];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0 || fd >= OPEN_MAX)
		return (free(stash[fd]), stash[fd] = NULL, NULL);
	if (stash[fd] == NULL)
		stash[fd] = ft_strdup("");
	stash[fd] = read_and_stash(fd, stash[fd]);
	if (stash[fd] == NULL)
		return (NULL);
	line = extract_line(stash[fd]);
	stash[fd] = clean_stash(stash[fd]);
	if (line == NULL && stash[fd] != NULL)
	{
		free(stash[fd]);
		stash[fd] = NULL;
	}
	return (line);
}

// int	main(void)
// {
// 	int		fd_sample;
// 	int		fd_sam;
// 	char	*line;
// 	int		i;

// 	// fd = 0;
// 	fd_sample = open("sample.txt", O_RDONLY);
// 	fd_sam = open("sam.txt", O_RDONLY);

// 	if (fd_sam == -1 || fd_sample == -1)
// 	{
// 		perror("open");
// 		return (1);
// 	}
// 	i = 0;
// 	printf("%d\n",fd_sample);
// 	printf("%d\n",fd_sam);

// 	line = get_next_line(fd_sample);
// 	printf("sample:%s", line);
// 	free(line);

// 	line = get_next_line(fd_sample);
// 	printf("sample:%s", line);
// 	free(line);

// 	line = get_next_line(fd_sam);
// 	printf("sam   :%s", line);
// 	free(line);

// 	line = get_next_line(fd_sample);
// 	printf("sample:%s", line);
// 	free(line);

// 	line = get_next_line(fd_sample);
// 	printf("sample:%s", line);
// 	free(line);

// 	line = get_next_line(fd_sam);
// 	printf("sam   :%s", line);
// 	free(line);

// 	line = get_next_line(fd_sample);
// 	printf("sample:%s", line);
// 	free(line);

// 	line = get_next_line(fd_sam);
// 	printf("sam   :%s", line);
// 	free(line);

// 	close(fd_sample);
// 	close(fd_sam);
// 	return (0);
// }
