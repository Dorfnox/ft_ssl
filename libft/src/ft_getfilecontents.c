/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getfilecontents.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/15 20:15:18 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/15 20:32:14 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*free_fc(int fd, char *fc)
{
	close(fd);
	free(fc);
	return (NULL);
}

char		*getfilecontents(char *filename)
{
	char	*filecontents;
	char	buff[1024];
	int		fd;
	int		ret;

	if ((fd = open(filename, O_RDONLY)) == -1)
		return (NULL);
	filecontents = ft_strnew(0);
	while ((ret = read(fd, buff, 1023)))
	{
		if (ret == -1)
			return (free_fc(fd, filecontents));
		buff[ret] = 0;
		if (!(filecontents = ft_strfjoin(&filecontents, buff)))
			return (free_fc(fd, filecontents));
	}
	close(fd);
	return (filecontents);
}
