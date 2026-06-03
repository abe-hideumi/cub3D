/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_calculations.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: knomura <knomura@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/02 13:38:56 by knomura           #+#    #+#             */
/*   Updated: 2026/06/02 13:38:57 by knomura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "display.h"

double	rotate_right_x(double dir_x, double dir_y)
{
	return (dir_x * cos(ROTATE_SPEED) - dir_y * sin(ROTATE_SPEED));
}

double	rotate_right_y(double dir_x, double dir_y)
{
	return (dir_x * sin(ROTATE_SPEED) + dir_y * cos(ROTATE_SPEED));
}

double	rotate_left_x(double dir_x, double dir_y)
{
	return (dir_x * cos(-ROTATE_SPEED) - dir_y * sin(-ROTATE_SPEED));
}

double	rotate_left_y(double dir_x, double dir_y)
{
	return (dir_x * sin(-ROTATE_SPEED) + dir_y * cos(-ROTATE_SPEED));
}
