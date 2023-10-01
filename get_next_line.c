#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif

#define TRUE 1
#define FALSE 0

#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != 0)
		i++;
	return (i);
}

char	*as_strjoin(char *str1, char *str2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = malloc(ft_strlen(str2) + ft_strlen(str1) + 1);
	if (str1)
	{	
		while (str1[i] != 0)
		{
			str[i] = str1[i];
			i++;
		}
	}
	while (str2[j] != 0)
	{
		str[i] = str2[j];
		i++;
		j++;
	}
	str[i] = 0;
	return (str);
}

int	check_nl(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '\n')
			return (TRUE);
		i++;
	}
	return (FALSE);
}

int	get_length(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\n' && str[i] != '\0')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

char	*get_line(char *str)
{
	int		i;
	int		len;
	char	*line;

	i = 0;
	len = get_length(str);
	line = (char *)malloc(len + 1);
	while (len > 0)
	{
		line[i] = str[i];
		i++;
		len--;
	}
	line[i] = '\0';
	return (line);
}

char	*modify_store(char *str)
{
	char	*new_temp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	new_temp = (char *)malloc(ft_strlen(str) - get_length(str) + 1);
	while (str[i] != 0 && str[i] != '\n')
		i++;
	if (str[i] == 0)
		return (NULL);
	i++;
	while (str[i] != 0)
	{
		new_temp[j] = str[i];
		i++;
		j++;
	}
	new_temp[j] = 0;
	free(str);
	return (new_temp);
}

char	*as_get_next_line(int fd)
{
	static char	*temp;
	char		*buf;
	char		*cur_line;
	int			rd;

	buf = malloc(BUFFER_SIZE + 1);
	while ((rd = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		if (rd < BUFFER_SIZE)
			buf[rd] = 0;
		temp = as_strjoin(temp, buf);
		if (check_nl(buf))
			break ;
	}
	if (rd == -1)
		return (NULL);
	free(buf);
	cur_line = get_line(temp);
	temp = modify_store(temp);
	return (cur_line);
}

int	main(void)
{
	int		i;
	int		fd;
	char	*line;

	i = 0;
	fd = open("./test.txt", O_RDONLY);
	while (i < 5)
	{
		line = as_get_next_line(fd);
		if (!line)
			return (0);
		printf("%d:", i);
		printf("%s\n", line);
		i++;
	}
	close(fd);
	return (0);
}
