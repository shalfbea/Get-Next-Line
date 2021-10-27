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
	//char	input;

	/*
	file = open("gnlTester/files/41_no_nl", O_RDONLY);
	s = get_next_line(file);
	printf("%s", s);
	free(s);
	s = get_next_line(file);
	printf("%s", s);
	free(s);
	*/
	//file = open("gnlTester/files/41_no_nl", O_RDONLY);
	//file = open("file4read.txt", O_RDONLY);
	file = open("gnlTester/files/multiple_nlx5", O_RDONLY);
	//file = open("gnlTester/files/nl", O_RDONLY);
	//scanf("%c", &input);
	size_t i = 0;
	while (i++ < 10)
	{
		s = get_next_line(file);
		printf("%s;", s);
		free(s);
		//scanf("%c", &input);
	}
	/*
	file = open("file4read.txt", O_RDONLY);
	s = get_next_line(file);
	printf("%s", s);
	free(s);
	s = get_next_line(file);
	printf("%s", s);
	s = get_next_line(file);
	printf("%s", s);
	free(s);
	scanf("%s", s);
	*/
	//s = get_next_line(file);
	//printf("%s", s);
	close(file);
}
