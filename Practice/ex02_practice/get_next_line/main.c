#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
	char *line;
	int ret = 0;
	int i = 1;

	while ((ret = get_next_line(&line)) > 0)
	{
		printf("ret: %d %d번째 줄: %s\n", ret, i++, line);
		free(line);
		line = NULL;
	}
	printf("%s\n", line);
	free(line);
	line = NULL;
	return 0;
}
