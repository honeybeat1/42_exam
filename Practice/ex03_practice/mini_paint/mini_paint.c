#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

#define ERR1 "Error: argument"
#define ERR2 "Error: Operation file corrupted"

FILE *file = NULL;
char z[302][302];
char bc, mode, c;
int zw, zh;
float cx, cy, r;

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
	float x, y, d;

	y = -1;
	while (++y < zh)
	{
		x = -1;
		while (++x < zw)
		{
			d = sqrtf(powf(cx - x, 2) + powf(cy - y, 2));
			if (r < d)
				continue ;
			else if (mode == 'C' || r - d < 1.0000000)
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
	if (!(file = fopen(argv[1], "r")) ||
			(fscanf(file, "%d %d %c\n", &zw, &zh, &bc) != 3) ||
			(zw <= 0 || 300 < zw || zh <= 0 || 300 <= zh))
		return (put_error(ERR2));
	memset(z, bc, sizeof(z));
	while (0 < (ret = fscanf(file, "%c %f %f %f %c\n", &mode, &cx, &cy, &r, &c)))
	{
		if ((mode != 'C' && mode != 'c') || r <= 0 || ret != 5)
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




