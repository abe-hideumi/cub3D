
#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include "map.h"
# include "display/display.h"

# ifdef __linux__
#  include "minilibx-linux/mlx.h"
# else
#  include "minilibx_mms_20200219/mlx.h"
# endif

void	free_map(t_map *map);

#endif
