#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int ac, char *av[])
{
	if (ac != 2)
		return (printf("jjj\n"), 1);
	parse_map(av[1]);




	return (0);
}