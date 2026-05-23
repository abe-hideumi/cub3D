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
