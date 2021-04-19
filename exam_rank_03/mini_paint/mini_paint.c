#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#define ERR1 "Error: argument"
#define ERR2 "Error: Operation file corrupted"

FILE	*file=NULL;
char	zone[302][302];
char	back_c, mode, c;
int		zone_w, zone_h;
float	center_x, center_y, r;

int		ft_strlen(char *s)
{
	int	i=0;

	while (s[i])
		i++;
	return (i);
}

void	put_str_newline(char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

int		put_error(char *s)
{
	if (file)
		fclose(file);
	put_str_newline(s);
	return (1);
}

void	draw_circle(void)
{
	float	x, y, d;

	y = -1;
	while (++y < zone_h)
	{
		x = -1;
		while (++x < zone_w)
		{
			d = sqrtf(powf(center_x-x, 2) + powf(center_y-y, 2));
			if (r < d)
				continue ;
			else if (mode=='C' || r-d<1.0000000)
				zone[(int)y][(int)x] = c;
		}
	}
}

int		main(int argc, char **argv)
{
	int	ret, i=-1;

	if (argc != 2)
		return (put_error(ERR1));
	if (!(file = fopen(argv[1], "r")) ||
		(fscanf(file, "%d %d %c\n", &zone_w, &zone_h, &back_c) != 3) ||
		(zone_w<=0 || 300<zone_w || zone_h<=0 || 300<zone_h))
		return (put_error(ERR2));
	memset(zone, back_c, sizeof(zone));
	while (0 < (ret=fscanf(file, "%c %f %f %f %c\n", &mode, &center_x, &center_y, &r, &c)))
	{
		if ((mode!='C' && mode!='c') || r<=0 || ret!=5)
			return (put_error(ERR2));
		draw_circle();
	}
	while (++i < zone_h)
	{
		zone[i][zone_w] = '\0';
		put_str_newline(zone[i]);
	}
	fclose(file);
	return (0);
}