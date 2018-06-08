/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/07 18:53:38 by bpierce           #+#    #+#             */
/*   Updated: 2018/06/07 19:00:49 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *src, size_t n)
{
	size_t	i;
	char	*output;

	if (!src || !n)
		return (NULL);
	if (!(output = malloc(sizeof(char) * (n + 1))))
		return (NULL);
	i = 0;
	while (i < n && src[i])
	{
		output[i] = src[i];
		++i;
	}
	while (i < n)
		output[i++] = 0;
	output[n] = 0;
	return (output);
}
