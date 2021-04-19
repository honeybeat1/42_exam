#include <unistd.h>

int main(int argc, char **argv)
{
	int i, j;
	int used[255];

	if (argc == 3)
	{
		i = 0;
		while (i < 255)
			used[i++] = 0;
		i = 2;

		while (i > 0)
		{
			j = 0;
			while (argv[i][j])
			{
				if (i == 2 && !used[(unsigned int)argv[i][j]])
					used[(unsigned int)argv[i][j]] = 1;
				else if (i == 1 && used[(unsigned int)argv[i][j]] == 1)
				{
					write(1, &argv[i][j], 1);
					used[(unsigned int)argv[i][j]] = 2;
				}
				j++;
			}
			i--;
		}
	}
	write(1, "\n", 1);
	return (0);
}
