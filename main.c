#include "get_next_line.h"

int	main(void)
{
	int fd;
	char *line;

	fd = open("txt.txt", O_RDONLY);
	get_next_line(fd, &line);
	return (0);
}
