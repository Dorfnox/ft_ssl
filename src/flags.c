/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:03:02 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/19 15:03:09 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

int					collect_given_parameter(char ***save, char *param)
{
	char	**tmp;
	int		i;

	if (!param)
		return (0);
	if ((tmp = *save))
	{
		i = -1;
		while (tmp[++i])
			;
		tmp = malloc(sizeof(char *) * (i + 2));
		ft_memcpy(tmp, *save, sizeof(char *) * i);
		tmp[i] = param;
		tmp[i + 1] = NULL;
	}
	else
	{
		tmp = malloc(sizeof(char *) * 2);
		tmp[0] = param;
		tmp[1] = NULL;
	}
	free(*save);
	*save = tmp;
	return (1);
}