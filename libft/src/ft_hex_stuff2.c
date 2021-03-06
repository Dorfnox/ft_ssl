/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_stuff2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpierce <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/28 13:16:59 by bpierce           #+#    #+#             */
/*   Updated: 2018/08/30 18:46:28 by bpierce          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
**	The character string should be 16 hex characters in length
**	But will work with what it gets
**	_be assumes that the given hex string is written in big endian order
**	ex: "ABC" would assume the 'A' comes first
**	resulting uint64_t would be : 10101011 11000000 00000000 00000000...
**								  A   B    C
*/

uint64_t	hex_str_to_64bit_be(char *s)
{
	int			i;
	uint64_t	message;

	if (!s)
		return (0);
	i = -1;
	message = 0;
	while (*s && ++i < 16)
	{
		message |= ((uint64_t)convert_hex_char_to_4bit(*s)) << (60 - (4 * i));
		++s;
	}
	return (message);
}

/*
**	Does the same as above, but for uint64_t to 16-char string
*/

char		*bit64_to_hex_str_be(uint64_t x)
{
	int		i;
	char	*s;
	char	*hex;

	hex = "0123456789ABCDEF";
	if (!(s = ft_memalloc(sizeof(char) * 17)))
		return (NULL);
	i = -1;
	while (++i < 16)
		s[i] = hex[(x >> (i * 4)) & 15];
	return (s);
}

/*
**	The character string should be 16 hex characters in length
**	But will work with what it gets
**	_le assumes that the given hex string is written in little endian order
**	ex: "ABC" would assume the 'C' comes first
**	resulting uint64_t would be : ...00000000 00000000 00001100 10101011
**														   C	A	B
*/

uint64_t	hex_str_to_64bit_le(char *s)
{
	int			i;
	uint64_t	message;
	uint64_t	tmp;

	if (!s)
		return (0);
	i = -1;
	message = 0;
	while (*s && ++i < 8)
	{
		tmp = ((uint64_t)convert_hex_char_to_4bit(*s)) << 4;
		++s;
		if (*s)
			tmp |= (uint64_t)convert_hex_char_to_4bit(*s);
		message |= tmp << (8 * i);
		if (*s)
			++s;
	}
	return (message);
}

/*
**	Does the same as above, except opposite, and returns a 16-char string
*/

char		*bit64_to_hex_str_le(uint64_t x)
{
	int		i;
	char	*s;
	char	*hex;

	hex = "0123456789ABCDEF";
	if (!(s = ft_memalloc(sizeof(char) * 17)))
		return (NULL);
	i = -1;
	while (++i < 16)
		s[i] = hex[(x >> (60 - (i * 4))) & 15];
	return (s);
}

/*
** Given 64-bit data, write that into the area where s is pointing to
*/

void		insert_64bit_into_string(char *s, uint64_t b)
{
	int		i;

	if (s)
	{
		i = -1;
		while (++i < 8)
			s[i] = (b >> (56 - (i * 8))) & 0xFF;
	}
}
