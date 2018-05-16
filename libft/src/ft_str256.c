/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str256.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/14 18:53:04 by bpierce           #+#    #+#             */
/*   Updated: 2018/05/14 20:47:34 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Builds a static string given 'num' of strings to concatenate together
** Stores 255 characters without 'overloading' the buffer
*/

char	*ft_str256(int num, ...)
{
	static char	s[256];
	char		*tmp;
	int			i;
	va_list		ap;

	i = 0;
	s[255] = 0;
	va_start(ap, num);
	while (num--)
	{
		if ((tmp = va_arg(ap, char *)))
			while (i < 255 && *tmp)
				s[i++] = *(tmp++);
		if (tmp && *tmp)
		{
			s[251] = '.';
			s[252] = '.';
			s[253] = '.';
			s[254] = '\n';
			break ;
		}
	}
	s[i] = 0;
	va_end(ap);
	return (s);
}

/*
** Same thing, but with a bigger buffer
*/

char	*ft_str1024(int num, ...)
{
	static char	s[1024];
	char		*tmp;
	int			i;
	va_list		ap;

	i = 0;
	s[1023] = 0;
	va_start(ap, num);
	while (num--)
	{
		if ((tmp = va_arg(ap, char *)))
			while (i < 1023 && *tmp)
				s[i++] = *(tmp++);
		if (tmp && *tmp)
		{
			s[1022] = '\n';
			s[1021] = '.';
			s[1020] = '.';
			s[1019] = '.';
			break ;
		}
	}
	s[i] = 0;
	va_end(ap);
	return (s);
}

/*
** Same thing, but with a smaller buffer
*/

char	*ft_str128(int num, ...)
{
	static char	s[128];
	char		*tmp;
	int			i;
	va_list		ap;

	i = 0;
	s[127] = 0;
	va_start(ap, num);
	while (num--)
	{
		if ((tmp = va_arg(ap, char *)))
			while (i < 127 && *tmp)
				s[i++] = *(tmp++);
		if (tmp && *tmp)
		{
			s[126] = '\n';
			s[125] = '.';
			s[124] = '.';
			s[123] = '.';
			break ;
		}
	}
	s[i] = 0;
	va_end(ap);
	return (s);
}
