/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lcros-mo <lcros-mo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/18 00:18:29 by lcros-mo          #+#    #+#             */
/*   Updated: 2020/07/27 17:21:57 by lcros-mo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	int i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

char		*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

static int	ft_new_line(char **cache, char **line, int fd)
{
	int		len;
	char	*w;

	len = 0;
	while (cache[fd][len] != '\n' && cache[fd][len] != '\0')
		len++;
	if (cache[fd][len] == '\n')
	{
		*line = ft_substr(cache[fd], 0, len);
		w = ft_strdup(&cache[fd][len + 1]);
		free(cache[fd]);
		cache[fd] = w;
		if (cache[fd][0] == '\0')
			ft_strdel(&cache[fd]);
	}
	else
	{
		*line = ft_strdup(cache[fd]);
		ft_strdel(&cache[fd]);
		return (0);
	}
	return (1);
}

static	int	ft_return(char **cache, char **line, int fd, int r)
{
	if (r < 0)
		return (-1);
	if (r == 0 && cache[fd] == NULL)
	{
		*line = ft_strdup("");
		return (0);
	}
	return (ft_new_line(cache, line, fd));
}

int			get_next_line(int fd, char **line)
{
	static	char	*cache[4096];
	char			*mem;
	char			*w;
	int				r;

	if (fd < 0 || line == NULL || BUFFER_SIZE < 1 
    || !(mem = malloc((sizeof(char) * BUFFER_SIZE) + 1)))
		return (-1);
	while ((r = read(fd, mem, BUFFER_SIZE)) > 0)
	{
		mem[r] = '\0';
		if (cache[fd] == NULL)
			cache[fd] = ft_strnew(1);
		w = ft_strjoin(cache[fd], mem);
		free(cache[fd]);
		cache[fd] = w;
		if (ft_strchr(mem, '\n'))
			break ;
	}
	free(mem);
	return (ft_return(cache, line, fd, r));
}