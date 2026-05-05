#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "map.h"

int main(int ac, char *av[])
{
	if (ac != 2)
		return (printf("jjj\n"), 1);
	t_info info;

	parse_map(av[1], info);




	return (0);
}