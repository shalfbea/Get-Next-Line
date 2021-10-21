#include "get_next_line.h"
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <libgen.h>

int	main(void)
{
	char	*s;
	int		file;

	file = open("gnlTester/files/41_no_nl", O_RDONLY);
	s = get_next_line(file);
	printf("%s", s);
	free(s);
	s = get_next_line(file);
	printf("%s", s);
	free(s);
	scanf("%s", s);
	/*
	file = open("file4read.txt", O_RDONLY);
	s = get_next_line(file);
	printf("%s", s);
	free(s);
	s = get_next_line(file);
	printf("%s", s);
	s = get_next_line(file);
	printf("%s", s);
	s = get_next_line(file);
	printf("%s", s);
	*/
	close(file);
}
