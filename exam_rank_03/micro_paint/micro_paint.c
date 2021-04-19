#include <unistd.h>
#include <stdio.h>
#include <string.h>
#define ERR1 "Error: argument"
#define ERR2 "Error: Operation file corrupted"

FILE *file = NULL;
char zone[302][302];
char back_c, mode, c;
int zone_w, zone_h;
float corner_x, corner_y, rec_w, rec_h;

int ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return (i);
}

void put_str_newline(char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

int put_error(char *s)
{
	if (file)
		fclose(file);
	put_str_newline(s);
	return (1);
}

void draw_rec(void)
{
	float x, y;

	y = -1;
	while (++y < zone_h)
	{
		x = -1;
		while (++x < zone_w)
		{
			if (x < corner_x || corner_x + rec_w < x || y < corner_y || corner_y + rec_h < y)
				continue;
			else if (mode == 'R' || x < corner_x + 1.0000000 || corner_x + rec_w - 1.0000000 < x || y < corner_y + 1.0000000 || corner_y + rec_h - 1.0000000 < y)
				zone[(int)y][(int)x] = c;
		}
	}
}

int main(int argc, char **argv)
{
	int ret, i = -1;

	if (argc != 2)
		return (put_error(ERR1));
	if (!(file = fopen(argv[1], "r")) ||
		(fscanf(file, "%d %d %c\n", &zone_w, &zone_h, &back_c) != 3) ||
		(zone_w <= 0 || 300 < zone_w || zone_h <= 0 || 300 < zone_h))
		return (put_error(ERR2));
	memset(zone, back_c, sizeof(zone));
	while (0 < (ret = fscanf(file, "%c %f %f %f %f %c\n", &mode, &corner_x, &corner_y, &rec_w, &rec_h, &c)))
	{
		if ((mode != 'R' && mode != 'r') || rec_w <= 0 || rec_h <= 0 || ret != 6)
			return (put_error(ERR2));
		draw_rec();
	}
	while (++i < zone_h)
	{
		zone[i][zone_w] = '\0';
		put_str_newline(zone[i]);
	}
	fclose(file);
	return (0);
}
