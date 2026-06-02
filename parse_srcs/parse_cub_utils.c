/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:39:37 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 18:40:18 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "map.h"

static size_t	get_old_size(char **ptr)
{
	size_t	size;

	size = 0;
	while (ptr[size] != NULL)
		size++;
	return (size);
}

char	**ft_realloc(char **ptr, size_t new_size)
{
	char	**new_ptr;
	size_t	old_size;
	size_t	copy_size;

	if (new_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (malloc(sizeof(char *) * new_size + 1));
	new_ptr = malloc(sizeof(char *) * new_size + 1);
	if (new_ptr == NULL)
		return (NULL);
	old_size = get_old_size(ptr);
	if (old_size < new_size)
		copy_size = old_size;
	else
		copy_size = new_size;
	ft_memcpy(new_ptr, ptr, sizeof(char *) * copy_size);
	new_ptr[copy_size] = NULL;
	free(ptr);
	return (new_ptr);
}

bool	ft_is_space(char c)
{
	if (c == ' ' || c == '\t')
		return (true);
	return (false);
}

void	put_error_free(char *msg, t_info *info, char *str)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
	free_parse_info(info, str);
}

void	put_error(char *msg)
{
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("\n", 2);
}
