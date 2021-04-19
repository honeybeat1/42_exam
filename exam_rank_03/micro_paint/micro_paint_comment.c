#include <unistd.h>  // write
#include <stdio.h>  // fscanf, fopen, fclose
#include <string.h>  // memset
#define ERR1 "Error: argument"  // 에러코드1 매크로
#define ERR2 "Error: Operation file corrupted"  // 에러코드2 매크로

FILE	*file=NULL;  // 오픈할 파일
char	zone[302][302];  // 출력할 직사각형
char	back_c, mode, c;  // 기본으로 채워질 배경, 텅빈 직사각형인지 꽉찬 직사각형인지, 그려질 문자
int		zone_w, zone_h;  // 직사각형 너비, 높이
float	corner_x, corner_y, rec_w, rec_h;  // 그려질 직사각형의 왼쪽 상단의 모서리의 x좌표, y좌표, 그려질 직사각형의 너비, 높이

// 문자열의 길이를 반환하는 함수
int		ft_strlen(char *s)
{
	int i=0;

	while (s[i])
		i++;
	return (i);
}

// 문자열과 개행을 출력하는 함수
void	put_str_newline(char *s)
{
	write(1, s, ft_strlen(s));
	write(1, "\n", 1);
}

// 파일이 열려있으면 닫고, 에러메세지를 출력하고, 항상 1을 반환하는 함수
int		put_error(char *s)
{
	if (file)
		fclose(file);
	put_str_newline(s);
	return (1);  // 에러처리를 위해 항상 1을 반환
}

void	draw_rec(void)  // 직사각형에 문자 채우기
{
	float	x, y;

	y = -1;
	while (++y < zone_h)
	{
		x = -1;
		while (++x < zone_w)
		{
			if (x<corner_x || corner_x+rec_w<x || y<corner_y || corner_y+rec_h<y)  // 출력할 직사각형의 범위를 넘어가면
				continue ;
			// 꽉채우는 직사각형 이거나 텅빈 직사각형일때 테두리거나
			else if (mode=='R' || x<corner_x+1.0000000 || corner_x+rec_w-1.0000000<x || y<corner_y+1.0000000 || corner_y+rec_h-1.0000000<y)
				zone[(int)y][(int)x] = c;  // 문자 채우기
		}
	}
}

int		main(int argc, char **argv)
{
	int	ret, i=-1;

	if (argc != 2)  // main함수의 인자가 1개가 아니면,
		return (put_error(ERR1));  // 에러코드1과 개행을 출력하고, 1을 반환하며 프로그램 종료
	// 출력될 직사각형의 너비, 높이, 기본으로 채워지는 문자 읽기
	// 파일 오픈에 실패하거나,
	// 너비,높이,기본으로 채워지는 문자 총3개를 읽지 못하거나,
	// 출력될 직사각형의 범위가 잘못 되었다면
	if (!(file = fopen(argv[1], "r")) ||  // 읽기모드로 파일오픈
		(fscanf(file, "%d %d %c\n", &zone_w, &zone_h, &back_c) != 3) ||
		(zone_w<=0 || 300<zone_w || zone_h<=0 || 300<zone_h))
		return (put_error(ERR2));  // 에러코드2와 개행을 출력하고, 1을 반환하며 프로그램 종료
	memset(zone, back_c, sizeof(zone));  // 직사각형에 배경이될 문자를 채우기
	// 그려질 직사각형의 정보 읽기
	while (0 < (ret=fscanf(file, "%c %f %f %f %f %c\n", &mode, &corner_x, &corner_y, &rec_w, &rec_h, &c)))
	{
		// 약속된 mode('r' or 'R') 가 아니거나,
		// 그려질 직사각형의 너비나 높이가 음수거나,
		// 6개 정보를 다읽지 못한다면
		if ((mode!='R' && mode!='r') || rec_w<=0 || rec_h<=0 || ret!=6)
			return (put_error(ERR2));  // 에러코드2와 개행을 출력하고, 1을 반환하며 프로그램 종료
		draw_rec();  // 읽은 정보를 바탕으로 직사각형에 문자 채우기
	}
	while (++i < zone_h)
	{
		zone[i][zone_w] = '\0';  // 각문자열 끝에 널문자 채우기
		put_str_newline(zone[i]);  // 한줄과 개행출력
	}
	fclose(file);  // 파일 닫기
	return (0);  // 0을 반환하여 프로그램이 정상종료됨을 알려줌
}