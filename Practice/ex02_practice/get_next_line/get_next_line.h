#ifndef GET_NEXT_LINE_H
#define GET_NEXT_LINE_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>

int get_next_line(char **line);

int ft_strlen(char *s);
char *ft_strdup(char *s);
char *ft_strchr(char *s, int c);
char *ft_strjoin(char *s1, char *s2);
char *substr(const char *s, unsigned int start, size_t len);

#endif
