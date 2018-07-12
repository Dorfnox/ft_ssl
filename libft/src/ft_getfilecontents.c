/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfilecontents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:15:18 by bpierce           #+#    #+#             */
/*   Updated: 2018/07/11 23:49:46 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	free_contents(int fd, uint8_t **contents)
{
	if (fd != -1)
		close(fd);
	free(*contents);
	*contents = NULL;
	return (0);
}

size_t			getfilecontents(char *filename, uint8_t **contents)
{
	char	buff[1024];
	int		fd;
	int		ret;
	size_t	total;

	if (!filename || !contents)
		return (0);
	if ((fd = open(filename, O_RDONLY)) == -1)
		return (free_contents(fd, contents));
	if (!(*contents = malloc(1)))
		return (free_contents(fd, contents));
	total = 0;
	while ((ret = read(fd, buff, 1023)))
	{
		if (ret == -1)
			return (free_contents(fd, contents));
		buff[ret] = 0;
		if (!(*contents = ft_rememalloc(*contents, total, total + ret)))
			return (free_contents(fd, contents));
		ft_memcpy(&(*contents)[total], buff, ret);
		total += ret;
	}
	close(fd);
	return (total);
}

size_t			writetofile(char *filename, uint8_t *contents, size_t len)
{
	int		ret;
	int		fd;

	if (!filename || !contents)
		return (0);
	if ((fd = open(filename, O_TRUNC | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR))
			== -1)
		return (0);
	ret = write(fd, contents, len);
	close(fd);
	return (ret == -1 ? 0 : len);
}
