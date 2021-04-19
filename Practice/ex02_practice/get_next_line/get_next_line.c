#include "get_next_line.h"

int ft_strlen(char *s)
{
	int i;

	i = 0;
	if (s == NULL)
		return (0);
	while (s[i])
		i++;
	return (i);
}

char *ft_strdup(char *s)
{
	int i;
	int len;
	char *dup;

	if (s == NULL)
		return (0);
	i = 0;
	len = ft_strlen(s);
	dup = (char *)malloc(sizeof(char) * (len + 1));
	if (!dup)
		return (NULL);
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}

char *ft_strchr(char *s, int c)
{
	if (!s)
		return (NULL);
	while (*s != c)
	{
		if (*s == '\0')
			return (NULL);
		++s;
	}
	return (s);
}

char *ft_strjoin(char *s1, char *s2)
{
	int i;
	char *join;

	i = 0;
	if (!(join = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1))))
		return NULL;
	while (*s1)
		join[i++] = *s1++;
	while (*s2)
		join[i++] = *s2++;
	join[i] = '\0';
	return (join);
}

char *ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t slen;
	size_t i;
	char *sub;

	if (!s)
		return (NULL);
	i = 0;
	slen = (size_t)ft_strlen((char *)s);
	sub = (char *)malloc(sizeof(char) * (len + 1));
	if (!sub)
		return (NULL);
	while (i < len && start < slen)
	{
		sub[i++] = s[start++];
	}
	sub[i] = '\0';
	return (sub);
}

int get_next_line(char **line)
{
	static char *str;
	char buf[1024];
	char *temp;
	char *tp;
	int nread;

	nread = 1;
	while (((tp = ft_strchr(str, '\n')) == NULL) && nread != 0)
	{
		if ((nread = read(0, buf, 1024)) == -1)
			return (-1);
		buf[nread] = '\0';
		if (str == NULL)
			temp = ft_strdup(buf);
		else
			temp = ft_strjoin(str, buf);
		if (str != NULL)
			free(str);
		str = temp;
	}
	if (tp != NULL)
	{
		temp = str;
		*line = ft_substr(str, 0, tp - str);
		str = ft_strdup(tp + 1);
		free(temp);
		return (1);
	}
	*line = str;
	str = NULL;
	return (0);
}
