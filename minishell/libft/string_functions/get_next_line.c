/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gpirozzi <giovannipirozzi12345@gmail.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 15:21:43 by gpirozzi          #+#    #+#             */
/*   Updated: 2025/04/09 16:17:14 by gpirozzi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

#define BUFFER_SIZE	1

static char	*ft_putline(int fd, char **result, char *buffer)
{
	ssize_t	bt_read;
	char	*tmp;

	while (1)
	{
		bt_read = read(fd, buffer, BUFFER_SIZE);
		if (bt_read == -1)
		{
			free(*result);
			*result = NULL;
			return (NULL);
		}
		else if (bt_read == 0)
			break ;
		buffer[bt_read] = '\0';
		if (!*result)
			*result = ft_strdup("");
		tmp = *result;
		*result = ft_strjoin(tmp, buffer);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (*result);
}

static char	*ft_getrest(char *line)
{
	ssize_t	i;
	char	*rest;

	i = 0;
	while (line[i] != '\0' && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (NULL);
	rest = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (!rest)
	{
		free(rest);
		rest = NULL;
		return (NULL);
	}
	line[i + 1] = '\0';
	return (rest);
}

char	*get_next_line(int fd)
{
	static char	*rest;
	char		*buffer;
	char		*line;

	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		return (NULL);
	}
	line = ft_putline(fd, &rest, buffer);
	free(buffer);
	buffer = NULL;
	if (!line)
		return (NULL);
	rest = ft_getrest(line);
	return (line);
}
/* int main()
{
	char	*line;
	int	fd;

	fd = open("text.txt", O_WRONLY);
	while (1)
	{
		line = get_next_line(fd);
		if(!line)
			return(1);
		printf("%s", line);
		free(line);
	}
	close(fd);
} */
