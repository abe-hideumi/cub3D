/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cub_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: habe <habe@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:39:37 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 17:09:44 by habe             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "map.h"

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
