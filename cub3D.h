/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:39:17 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 13:39:18 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdbool.h>
# include "map.h"
# include "display/display.h"
# include "libft/libft.h"

# ifdef __linux__
#  include "minilibx-linux/mlx.h"
# else
#  include "minilibx_mms_20200219/mlx.h"
# endif

void	free_map(t_map *map);

#endif
