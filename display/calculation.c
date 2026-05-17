#include "display.h"

double	multiply(double a, double b)
{
	return (a * b);
}

double	rotate_right_x(double dir_x, double dir_y)
{
	return (dir_x * cos(ROT_SPEED) - dir_y * sin(ROT_SPEED));
}

double	rotate_right_y(double dir_x, double dir_y)
{
	return (dir_x * sin(ROT_SPEED) + dir_y * cos(ROT_SPEED));
}

double	rotate_left_x(double dir_x, double dir_y)
{
	return (dir_x * cos(-ROT_SPEED) - dir_y * sin(-ROT_SPEED));
}

double	rotate_left_y(double dir_x, double dir_y)
{
	return (dir_x * sin(-ROT_SPEED) + dir_y * cos(-ROT_SPEED));
}
