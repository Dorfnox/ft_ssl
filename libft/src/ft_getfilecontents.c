/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfilecontents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:15:18 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/16 15:00:39 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	free_fc(int fd, char **fc)
{
	close(fd);
	free(*fc);
	*fc = NULL;
	return (0);
}

size_t			getfilecontents(char *filename, char **contents)
{
	char	buff[1024];
	int		fd;
	int		ret;
	size_t	total;

	if (!filename || !contents || (fd = open(filename, O_RDONLY)) == -1)
		return (0);
	*contents = ft_strnew(0);
	total = 0;
	while ((ret = read(fd, buff, 1023)))
	{
		if (ret == -1)
			return (free_fc(fd, contents));
		buff[ret] = 0;
		if (!(*contents = ft_strfjoin(contents, buff)))
			return (free_fc(fd, contents));
		total += ret;
	}
	close(fd);
	return (total);
}
