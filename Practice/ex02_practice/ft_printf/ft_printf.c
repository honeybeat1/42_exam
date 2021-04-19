#include <unistd.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

va_list ap;
int precision;
int dot;
int width;
char type;

// stdout
int ft_putc(char c)
{
	write(1, &c, 1);
	return (1);
}

int ft_putcn(char c, int n)
{
	int temp;

	if (n <= 0)
		return (0);
	temp = n;
	while (temp--)
		ft_putc(c);
	return (n);
}

int ft_puts(char *s, int n)
{
	int i;

	i = 0;
	while (s[i] && i < n)
		ft_putc(s[i++]);
	return (i);
}

void ft_putn(long long num, int base)
{
	char *hex;

	hex = "0123456789abcdef";
	if (num < 0)
		num = -num;
	if (num >= base)
	{
		ft_putn(num / base, base);
		ft_putn(num % base, base);
	}
	else
		ft_putc(hex[num]);
}

// length
int ft_strlen(char *s)
{
	int i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int ft_dlen(int num)
{
	int i;

	i = 1;
	while (num /= 10)
		i++;
	return (i);
}

int ft_hlen(unsigned int num)
{
	int i;

	i = 1;
	while (num /= 16)
		i++;
	return (i);
}

// sdx
int print_s(void)
{
	int len;
	char *str;

	str = va_arg(ap, char *);
	if (!str)
		str = "(null)";
	len = ft_strlen(str);
	if (dot && precision > len)
		precision = len;
	return ft_putcn(' ', width - precision) + ft_puts(str, precision);
}

int print_d(void)
{
	int len;
	int ret;
	int neg;
	int num;

	num = va_arg(ap, int);
	neg = num < 0;
	len = ft_dlen(num);

	if (dot && num == 0 && precision == 0)
		return ft_putcn(' ', width);
	if (!dot || precision < len)
		precision = len;
	ret = ft_putcn(' ', width - precision - neg);
	if (neg)
		ret += ft_putc('-');
	ret += ft_putcn('0', precision - len);
	ft_putn(num, 10);
	return (ret + len);
}

int print_x(void)
{
	int len;
	int ret;
	unsigned int num;

	num = va_arg(ap, unsigned int);
	len = ft_hlen(num);
	if (dot && num == 0 && precision == 0)
		return ft_putcn(' ', width);
	if (!dot || precision < len)
		precision = len;
	ret = ft_putcn(' ', width - precision);
	ret += ft_putcn('0', precision - len);
	ft_putn(num, 16);
	return (ret + len);
}

// utils
int ft_isdigit(char c)
{
	return '0' <= c & c <= '9';
}

int setParam(char *s)
{
	int i;
	int temp;

	i = 0;
	width = 0;
	precision = 0;
	dot = 0;

	while (s[i])
	{
		char c = s[i];
		if (ft_isdigit(c))
		{
			temp = c - '0';
			if (!dot)
				width = (width * 10) + temp;
			else
				precision = (precision * 10) + temp;
		}
		else if (c == '.')
			dot = 1;
		else
			break;
		++i;
	}
	type = s[i++];
	return (i);
}

int parse(char *s)
{
	int i;
	int ret;

	i = 0;
	ret = 0;
	while (s[i])
	{
		if (s[i] != '%')
			ret += ft_putc(s[i]);
		else
		{
			i += setParam(s + i + 1);
			if (type == 's')
				ret += print_s();
			else if (type == 'd')
				ret += print_d();
			else
				ret += print_x();
		}
		++i;
	}
	return (ret);
}

// ft_printf
int ft_printf(const char *s, ...)
{
	va_start(ap, s);
	int ret = parse((char *)s);
	va_end(ap);
	return (ret);
}

// main
int main(void)
{
	ft_printf("--Required--\n");
	ft_printf("%10.2s\n", "toto");
	ft_printf("Magic %s is %5d\n", "number", 42);
	ft_printf("Hexadecimal for %d is %x\n", 42, 42);
}
