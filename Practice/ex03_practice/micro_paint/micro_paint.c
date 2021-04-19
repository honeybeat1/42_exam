#include <unistd.h>
#include <stdio.h>
#include <string.h>

#define ERR1 "Error: argument"
#define ERR2 "Error: Operation file corrupted"

FILE *file = NULL;
char z[302][302];
char bc, mode, c;
int zw, zh;
float cx, cy, rw, rh;

int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void put_str_nl(char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

int put_error(char *s)
{
	if (file)
		fclose(file);
	put_str_nl(s);
	return (1);
}

void draw(void)
{
	float x, y;

	y = -1;
	while (++y < zh)
	{
		x = -1;
		while (++x < zw)
		{
			if (x < cx || cx + rw < x || y < cy || cy + rh < y)
				continue;
			else if (mode == 'R' || x < cx + 1.0000000 || cx + rw - 1.0000000 < x || y < cy + 1.0000000 || cy + rh - 1.0000000 < y)
				z[(int)y][(int)x] = c;
		}
	}
}

int main(int argc, char **argv)
{
	int i = -1;
	int ret;

	if (argc != 2)
		return (put_error(ERR1));
	if (
		!(file = fopen(argv[1], "r")) ||
		(fscanf(file, "%d %d %c\n", &zw, &zh, &bc) != 3) ||
		(zw <= 0 || 300 < zw || zh <= 0 || 300 <= zh))
		return (put_error(ERR2));
	memset(z, bc, sizeof(z));
	while (
		0 < (ret = fscanf(file, "%c %f %f %f %f %c\n", &mode, &cx, &cy, &rw, &rh, &c)))
	{
		if ((mode != 'R' && mode != 'r') || rw <= 0 || rh <= 0 || ret != 6)
			return (put_error(ERR2));
		draw();
	}
	while (++i < zh)
	{
		z[i][zw] = '\0';
		put_str_nl(z[i]);
	}
	fclose(file);
	return (0);
}
